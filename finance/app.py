import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT username FROM users WHERE id == ?", session["user_id"])
    username = rows[0]["username"]
    #query bought history
    buys = db.execute("SELECT quote_bought, quote_name, SUM(shares) FROM purchases WHERE username == ? GROUP BY quote_bought", username)
    stock_total = 0
    for buy in buys:
        current_price = lookup(buy["quote_bought"])["price"]
        buy["price"] = usd(current_price)
        total = current_price * buy["SUM(shares)"]
        buy["total"] = usd(total)
        stock_total += total
    #balance
    cashs = db.execute("SELECT cash FROM users WHERE username = ?", username)
    cash = usd(cashs[0]["cash"])
    #total = cash + stock_total
    totals = usd(stock_total + cashs[0]["cash"])
    return render_template("index.html", buys=buys, cash=cash, totals=totals)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    #check for invalid input
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing symbol")
        elif lookup(symbol) == None:
            return apology("Invalid symbol!!")
        elif not request.form.get("shares"):
            return apology("Missing shares")
        elif int(request.form.get("shares")) <= 0:
            return apology("Invalid shares")

        cost = float(lookup(symbol)["price"]) * float(request.form.get("shares"))
        cashes = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])
        cash = cashes[0]["cash"]
        rows = db.execute("SELECT username FROM users WHERE id == ?", session["user_id"])
        username = rows[0]["username"]
        if cost <= cash:
            db.execute("INSERT INTO purchases(username, quote_bought, quote_name, shares, prices, total, date) VALUES (?,?,?,?,?,?, datetime())",
                        username,
                        symbol,
                        lookup(symbol)["name"],
                        request.form.get("shares"),
                        lookup(symbol)["price"],
                        cost)
            db.execute("UPDATE users SET cash = ? WHERE id == ? ", (cash - cost)  ,session["user_id"])
            #update history
            db.execute("INSERT INTO transactions(symbol, shares, price, date) VALUES(?,?,?,datetime())"
                                            ,symbol
                                            ,int(request.form.get("shares"))
                                            ,lookup(symbol)["price"])
            return redirect("/")
        else:
            return apology("Can't buy stock")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM transactions")
    for row in rows:
        row["price"] = usd(row["price"])
    return render_template("transaction.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing symbol")
        elif lookup(symbol) == None:
            return apology("Invalid symbol!!")
        return render_template("quoted.html", name=lookup(symbol)["name"] , price=usd(lookup(symbol)["price"]), symbol=lookup(symbol)["symbol"])

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        #check missing informations
        if not request.form.get("username"):
            return apology("Missing username", 403)
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Missing password", 403)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password do not match", 403)
        #check registered user
        rows = db.execute("SELECT * FROM users WHERE username == ?", request.form.get("username").strip())
        if len(rows) == 1:
            return apology("This name has already existed", 403)
        #add user to database
        db.execute("INSERT INTO users(username, hash) VALUES(?,?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
        #query new database
        rows = db.execute("SELECT * FROM users WHERE username == ?", request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
     #query the list of quotes
    rows = db.execute("SELECT username FROM users WHERE id == ?", session["user_id"])
    username = rows[0]["username"]

    if request.method == "POST":
        #checking input
        symbol = request.form.get("symbol")
        price = lookup(symbol)["price"]
        if not symbol:
            return apology("Missing symbol")
        elif not request.form.get("shares"):
            return apology("Missing shares")
        elif int(request.form.get("shares")) <= 0:
            return apology("Invalid shares")

        shares = db.execute("SELECT SUM(shares) FROM purchases WHERE username == ? AND quote_bought == ?", username, symbol)
        share = shares[0]["SUM(shares)"]
        if len(shares) == 0:
            return apology("You have no share")
        #check if user has enough shares to sell
        if int(request.form.get("shares")) > share:
            return apology("You have less shares than that")
        elif  int(request.form.get("shares")) < share:
            db.execute("UPDATE purchases SET shares == ? WHERE username == ? AND quote_bought == ?",
                                                share - int(request.form.get("shares")),
                                                username,
                                                symbol)
            #update cash
            db.execute("UPDATE users SET cash == cash + ? WHERE username == ?", price * int(request.form.get("shares")), username)
            #update history
            db.execute("INSERT INTO transactions(symbol, shares, price, date) VALUES(?,?,?,datetime())"
                                            ,symbol
                                            ,- int(request.form.get("shares"))
                                            ,lookup(symbol)["price"])
        else:
            db.execute("DELETE FROM purchases WHERE username == ? AND quote_bought == ?", username, symbol)
            db.execute("UPDATE users SET cash == cash + ? WHERE username == ?", price * int(request.form.get("shares")), username)
            #update history
            db.execute("INSERT INTO transactions(symbol, shares, price, date) VALUES(?,?,?,datetime())"
                                            ,symbol
                                            ,- int(request.form.get("shares"))
                                            ,lookup(symbol)["price"])

        return redirect("/")

    quotes = db.execute("SELECT quote_bought FROM purchases WHERE username == ?", username)
    return render_template("sell.html", quotes=quotes)


