#include <cs50.h>
#include <stdio.h>

int main(void)
{

int n = 6;

    for(int i = 0; i < n; i++)
    {
        for(int j = n - 1; j > i; j--)
        {
            printf(" ");
        }

        for(int j = -1; j < i; j++)
        {
            printf("#");
        }

        printf("  ");

        for(int j = -1; j < i; j++)
        {
            printf("#");
        }

    printf("\n");
    }
}