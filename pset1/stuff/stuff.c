#include <cs50.h>
#include <stdio.h>

void print(string s, int m);
int prompt(int n);

int main(void)
{
    int n;

     do
        {
            n = get_int("Height: ");

            while(n%2==0)
            {
                n = get_int("Height: ");
            }
        }

        while(n<1 || n>20);

    for(int i=0; i<n; i++)
    {
        if (i<=n/2 - 1/2)
        {
        print(" ", n/2 - 1/2 -i);
        print("#", i+1);
        print(" ", 2);
        print("#", i+1);
        printf("\n");
        }
        else if ( i>n/2 -1/2)
        {
            print(" ", i-(n-1)/2 );
            print("#", n-i);
            print(" ", 2);
            print("#", n-i);
            printf("\n");
        }
    }
}

    void print(string s, int m)
    {
        for(int i=0; i<m; i++)
        {
            printf("%s", s);
        }
    }


