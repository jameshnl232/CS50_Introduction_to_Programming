#include <stdio.h>
#include <cs50.h>
#include <string.h>

int mario(int n);
int j = 0;
int main(void)


{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while(height<1 || height>8);

    height = mario(height);

    return 0;
}

int mario( int n)
{
    if( n == 0)
    return 1;

    for(int i=1; i<n;i++)
    {
        printf(" ");

    }

    j++;
    for(int i = n - j; i < n;i++)
    {
        printf("#");
    }

    printf("  ");

    for(int i = n - j; i < n; i++)
    {
        printf("#");
    }

    printf("\n");


    return mario( n-1);
}