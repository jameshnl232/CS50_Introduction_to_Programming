#include <stdio.h>

void draw(int h);

int main(void)
{
    draw(5);
}

void draw(int h)
{
    if(h == 0)
    return;


    for(int i = 0; i < h; i++)
    {
        printf("#");
    }

    printf("\n");

    draw(h - 1);

}