#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("type here: ");

    for (int i = 0, n = strlen(s); i<n; i++)
    {
        if(s[i] >= 'a' && s[i] <= 'z')
        {
        printf("%c", s[i] - 32);
        printf("\n");
        }

        else
        {
            printf("%c", s[i]);
        }
    }
}

