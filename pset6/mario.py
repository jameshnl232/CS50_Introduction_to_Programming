from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n <= 8 and n > 0:
        break


for i in range(n):
    for j in range(n - i - 1):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for k in range(i + 1):
        print("#", end="")
    print() # equals to print(end="\n")
