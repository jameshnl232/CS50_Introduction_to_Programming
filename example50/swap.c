#include <stdio.h>

void swap(int* x, int* y);

int main(void)
{
    int x = 1;
    int y = 2;
    printf("x: %i\ny: %i\n", x, y);
        swap(&x, &y);
        printf("\n");
    printf("x: %i\ny: %i\n", x, y);
}
    void swap(int* x, int* y)
    {
        int tmp = *x;
        *x = *y;
        *y = tmp;
    }


