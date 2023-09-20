#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start, end, year;
    do
    {
        start = get_int("Start: ");

        end = get_int("End: ");

    }
    while (start<9 || start>=end);

    year = 0;
    while(start<end)
    {
        start= start + start/3 - start/4;
        year++;
    }
    printf("Years: %i\n", year);


}
