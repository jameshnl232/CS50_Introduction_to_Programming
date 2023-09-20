#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int S1,S2;
    // prompt for start population
    do
    {
        S1 = get_int("Start size: ");
    }
    while(S1<9);
    // prompt for end population
    do
    {
        S2 = get_int("End size: ");
    }
    while(S2<S1);
    // keep track of time
    int year = 0;

    while(S1<S2)
    {
        S1 = S1 + S1/3 - S1/4;
        year++;
    }
    printf("Year: %i\n", year);
}