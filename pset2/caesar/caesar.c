#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool check_digit( string argv);


char Alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};


int main( int argc, string argv[] )
{
    if( argc != 2 || atol(argv[1]) < 1 || !check_digit(argv[1]) )
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    long key = atol(argv[1]);


    string Text = get_string("plaintext: ");
    long x;

    for( int i = 0, n = strlen(Text); i<n; i++)
    {

        if( isalpha(Text[i]) && islower(Text[i]) )
        {
            x = Text[i] - 97;

            if( Text[i] + key >  'z')
            {
                x = (x + key) %  26;
                Text[i] =  Alphabet[x];
            }

            else if( Text[i] + key < 'z')
            {
                Text[i] = Text[i] + key;
            }

        }

        else if( isalpha(Text[i]) && isupper(Text[i]) )
        {
            x = Text[i] - 65 ;

            if( Text[i] + key > 'Z')
            {
                x = (x + key) % 26;
                Text[i] = Alphabet[x];
            }
            else if( Text[i] + key < 'Z')
            {
                Text[i] = Text[i] + key;
            }

            if( islower(Text[i]) )
            Text[i] = toupper(Text[i]);
        }

        else
        Text[i] = Text[i];


    }

    printf("ciphertext: %s\n", Text );

    return 0;


}

bool check_digit( string argv)
{
    for( int i = 0, n = strlen(argv); i<n; i++)
    {
        if( !isdigit(argv[i]) )
        return false;
    }
    return true;

}

