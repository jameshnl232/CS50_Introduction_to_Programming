#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

bool mastercard_check ( int first_2digit);
bool check_algorithm( int sum);

int main(void)
{
    long long number;
    do
    {
        number = get_long_long("Number: ");
    }
    while( number < 1);

    //Luhn's algorithm
    //group 1
    long long copy_number1 = number;
    long long copy_number2 = number;
    int sum = 0;
    int count = 0;
    long long N = number / 10;
    printf("%lli\n", N);
    long long first_digit = number;
    int first_2digit;
    while(N > 0)
    {
        int digit = N % 10;
        digit = digit * 2;
        N = N / 100;

        if (digit > 9)
        {
            int digit1 = digit % 10;
            digit = digit / 10;
            int digit2 = digit % 10;
            digit = digit1 + digit2;
        }
        sum += digit;
    }
    //group2
    while( number > 0)
    {
        int digit = number % 10;
        number = number / 100;
        sum += digit;
    }
    printf("%i\n", sum);

    //count the digits
    while( copy_number1 != 0)
    {
        copy_number1 = copy_number1 / 10;
        count++;
    }
    printf("%i\n", count);

    //first digit   //method to find first digit
    while( first_digit >= 10)
    {
        first_digit /= 10;
    }
    printf("%lli\n", first_digit);

    //first 2digits  // another method
    first_2digit = copy_number2 / pow(10, count - 2);
    printf("%i\n", first_2digit);

    if (check_algorithm(sum) && count == 15 && (first_2digit == 34 || first_2digit == 37) )
    {
        printf("AMEX\n");
    }
    else if(check_algorithm(sum) && count == 16 && mastercard_check (first_2digit) == true)
    {
        printf("MASTERCARD\n");
    }
    else if(check_algorithm(sum) && first_digit == 4 && (count == 13 || count == 16))
    {
        printf("VISA\n");
    }
    else
    printf("INVALID\n");

    return 0;
}

bool mastercard_check ( int first_2digit)
{
    for(int i = 51; i <= 55; i++)
    {
        if( i == first_2digit)
        return true;
    }
    return false;
}

bool check_algorithm( int sum)
{
    if( sum % 10 == 0)
    return true;
    else
    return false;
}