#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)

{
    string names[] = { "Bill", "Tina", "Kevin"};

    for( int i = 0; i <3; i++)
    {
        if(strcmp(names[i], "Kevin")== 0)
        {
            printf("Found!\n");
            return 0;
        }
    }
    printf("Not found!\n");
    return 1;
}