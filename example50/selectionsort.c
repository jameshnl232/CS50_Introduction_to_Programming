#include <stdio.h>
#include <cs50.h>

#define N 7

void swap( int* x, int* y) //dung pointer de swap, swap binh thuong k dc
{
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

int main(void)
{
    int numbers[N] = { 2, 3, 1, 4, 7, 5, 6 };

    for( int i = 0; i < N; i++ ) //loop1 cho N numbers
    {
        for(int j = i + 1; j < N; j++) //loop2 chay de so sanh tung so trong loop1 voi nhung so con lai
        {
            if( numbers[j] < numbers[i] )
            {
                swap( &numbers[j], &numbers[i] );
            }
        }
    }

    for(int i = 0; i < N; i++)
    {
        printf("%i\n", numbers[i]);
    }



}