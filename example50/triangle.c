#include <cs50.h>
#include <stdio.h>

bool triangle_sides(int x, int y, int z);

int main(void)
{
    int sides[3];
    for(int i=0; i<3; i++)
    {
        sides[i] = get_int("sides: ");
    }
    if(triangle_sides()
    {
        printf("it's a triangle!\n");
    }
    else
    {
        printf("it's not a triangle\n");
    }



}

bool triangle_sides( )
{
    if(x<0 || y<0 || z<0)
    return false;

    if ((x+y)<z || (x+z)<y || (y+z)<x)
    return false;

    else
    return true;
}