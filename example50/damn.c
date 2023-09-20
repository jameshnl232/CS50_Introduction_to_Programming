#include <cs50.h>
#include <stdio.h>
// dem so chu cai cua input
int main(void)
{
    string s = get_string("Input: ");

    int count = 0;

    for(int i = 0; s[i] != '\0'; i++)
    {
        count++;
    }

    printf("Number of letters: %i", count);
}