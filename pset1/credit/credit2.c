#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

bool check_sum(int sum_1, int sum_2);
int sum_1(long credit_card);
int sum_2(long credit_card);
bool mastercard_check(int first_2digits);

int main(void)
{
    long credit_card = get_long("Number: "); //prompt a cardnumber from user

    if(check_sum(sum_1(credit_card), sum_2(credit_card)) == false)
    {
        printf("INVALID\n");
        return 0;
    }
    //get the first digit and 2first digits
    int digits = (int)log10(credit_card); //Total number of digits - 1
    int numbers = digits + 1;

    int first_2digits = (int)(credit_card / pow(10, digits - 1));

    int first_digit = (int)(credit_card / pow(10, digits ));


    if((first_2digits == 34 || first_2digits == 37) && numbers == 15 )
    {
        printf("AMEX\n");
    }
    else if(first_digit == 4 && ( numbers == 13 || numbers == 16) )
    {
        printf("VISA\n");
    }
    else if(numbers == 16 && mastercard_check(first_2digits) )
    {
        printf("MASTERCARD\n");
    }
    else
        printf("INVALID\n");
    return 0;
}

// calculate the first part
int sum_1(long credit_card)
{
    //second to last digit
    long credit_card1 = credit_card/10;
    int sum1 = 0;
    int second_tolastdigit;
    int mul_digit;

    while(credit_card1 > 0)
    {
    second_tolastdigit = credit_card1%10; //take the secondtolastdigit
    mul_digit = second_tolastdigit*2;    //multiply it with 2

    if(mul_digit >= 10)
    {
        mul_digit = (mul_digit%10) + 1;
    }
    sum1 = sum1 + mul_digit;

    credit_card1 = credit_card1/100;
    }
    return sum1;
}

//calculate the second part
int sum_2(long credit_card)
{
    long credit_card2 = credit_card;
    int sum2 = 0;
    int last_digit;

    while(credit_card2 > 0)
    {
    last_digit = credit_card2%10; //take the lastdigit

    sum2 = sum2 + last_digit;

    credit_card2= credit_card2/100;
    }
    return sum2;
}

//check for the total sum
bool check_sum(int sum_1, int sum_2)
{
    int sum = sum_1 + sum_2;
    if(sum%10 == 0)
    {
        return true;
    }
    return false;
}

//check for mastercard
bool mastercard_check(int first_2digits)
{
    for(int i = 51; i < 56; i++)
    {
        if(first_2digits == i)
        return true;
    }
    return false;
}