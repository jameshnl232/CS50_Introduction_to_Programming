#include <stdio.h>
#include <cs50.h>

//print a pyramid using user's interger input

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while(height<1 || height>8); //prompt user for a number in range 1<number<8

    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j < height - i - 1; j++) //print the space
        {
            printf(" ");
        }

        for(int k = 0; k < i + 1; k++) //print the brick
        {
            printf("#");
        }

        printf("  "); // print the space inbetween

        for(int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        printf("\n");
    }
    return 0;
}