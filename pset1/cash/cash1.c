#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int quarter = 25;
    int dimes = 10;
    int nickels = 5;
    int pennies = 1;
    float dollars;
    do
    {
    dollars = get_float("Change owed: ");
    }
    while (dollars<0);

    int cents = round(dollars * 100);

    int change1;
    int coins = 0;
    if(cents>25)
    {
        while(cents>25)
        {
            cents= cents/25;
            coins++;
        }
    }

    else if(cents>10 && cents<25)
    {
        while(10<cents<25)
        {
            cents=cents/10;
            coins++;
        }
    }

    else if(cents>5 && cents<10)
    {
        while(5<cents<10)
        {
            cents=cents/5;
            coins++;
        }
    }

    else if(cents>1 && cents<5)
    {
        while(1<cents<5)
            {
                cents=cents/1;
                coins++;
            }
    }
    printf("Coins: %i\n", coins);
}
