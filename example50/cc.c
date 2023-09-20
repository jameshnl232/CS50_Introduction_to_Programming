#include <stdio.h>

void draw(int h)
{
    if ( h == 0)
    return;

    draw(h - 1);

    for( int i = 0; i < h; i++)
    {
        printf("#");
    }

    printf("\n");
}

int main(void)
{
    draw(6);
}