#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


bool check_letters(char letter);


int main(void)
{
    string Text = get_string("Text: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;
    int spaces = 0;

    for( int i = 0, n = strlen(Text); i<n; i++)
    {
        if( check_letters(Text[i]) )
        {
            letters++;
        }

        if( Text[i] == ' ')
          {
              spaces++;
              words = spaces + 1;
          }

        if( Text[i] == 33 || Text[i] == 46 || Text[i] == 63)
        {
            sentences++;
        }
    }

    float L = 100*letters/ (float) words;
    float S = 100*sentences/ (float) words;
    int grade =  (int) round( 0.0588*L - 0.296*S - 15.8 );

    if( grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if( grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
        printf("Grade %i\n", grade);

}


bool check_letters(char letter)
{
    if ('a' <= letter && letter <= 'z')
    {
        return true;
    }

    else if( 'A' <= letter && letter <= 'Z')
    {
        return true;
    }

    else
    return false;
}








