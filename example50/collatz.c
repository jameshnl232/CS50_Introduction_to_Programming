#include <cs50.h>
#include <stdio.h>

int fact(int n);
int main(void)

{
    int nummer = get_int("nummer: ");

    int x = fact(nummer);

    printf("steps: %i\n", x );

    return 0;
}

int fact(int n)
{
    int steps = 0;
    while(n > 0){
            if(n==1)
            return 0;
            else if((n%2)==0)
            {
                steps++;
                return fact(n/2);
            }
            else if((n%2)!=0)
            {
                steps++;
                return fact(3*n+1);

            }
        }
    return steps;
}
