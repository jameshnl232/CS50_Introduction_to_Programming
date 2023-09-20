from cs50 import get_int, get_string
import re
import math

def main():
    while True: #get the user's input
        number = get_int("Number: ")
        if number > 0:
            break

    #first digit

    #sum 1
    N = int(number / 10)
    copy_number1 = number
    copy_number2 = number
    counter = 0
    sum_digits = 0
    while N > 0:
        digit = N % 10
        digit = digit * 2
        N = int(N / 100)
        if digit > 9:
            digit1 = digit % 10
            digit = int(digit / 10)
            digit2 = digit % 10
            digit = digit1 + digit2
        sum_digits += digit
    #sum 2
    while number > 0:
        no_mult_digit = number % 10
        number = int(number / 100)
        sum_digits += no_mult_digit

    #length of digits
    while copy_number1 > 0:
        copy_number1 = int(copy_number1 / 10)
        counter += 1

    master_card = [51, 52, 53, 54, 55]
    amex = [34, 37]
    visa = [4]

    if algorithm and first_2digits(copy_number2) in master_card and counter == 16:
        print("MASTERCARD")
    elif algorithm and first_2digits(copy_number2) in amex and counter == 15:
        print("AMEX")
    elif algorithm and first_digit(copy_number2) in visa and counter == 13 or counter == 16:
        print("VISA")
    else:
        print("INVALID")

    #first digits
def first_digit(number):
    while int(number) >= 10:
        number = int(number / 10)
    return number

    #first_2digits
def first_2digits(number):
    digit_length = int(math.log(number, 10)) #actual length - 1
    first_2digits = int(number / pow(10, digit_length - 1))
    return first_2digits


def algorithm (sum_digits):
    if (sum_digits % 10) == 0:
        return true

if __name__=="__main__":
    main()
