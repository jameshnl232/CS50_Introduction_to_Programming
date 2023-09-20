#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

bool check_valid( string key);

int main(int argc, string argv[])
{
    string key = argv[1];

    //accept a single command-line argument
    if( argc != 2 )
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    if( strlen(key) != 26 || check_valid(key) != true )
    {
        printf("Invalid Key\n");
        return 1;
    }
    //prompt user for a string
    string plaintext = get_string("plaintext: ");

    //key-algorithm
    //map letters in key to alphabet
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    int x;
        for(int i = 0, n = strlen(plaintext); i<n; i++)
        {
            for(int j = 0, m = strlen(alphabet); j<m; j++)
            {
                if( isalpha(plaintext[i]) && alphabet[j] == tolower(plaintext[i]) )
                {
                    x = j;
                }
            }

            if(isupper(plaintext[i]) && isalpha(plaintext[i]) )
            plaintext[i] = toupper(key[x]);
            else if( islower(plaintext[i]) && isalpha(plaintext[i]) )
            plaintext[i] = tolower(key[x]);
        }

    printf("ciphertext: %s\n", plaintext);
    return 0;
}

bool check_valid( char* key)
{
    int n = strlen(key);

    if( n != 26)
    return false;

    for(int i = 0; i<n; i++)
    {
        for(int j = i + 1; j<n; j++)
        {
            if ( tolower(key[i]) ==  tolower(key[j]))
            return false;
        }
    }

    for( int i = 0; i<n; i++)
    {
        if( !isalpha(key[i]) )
        return false;
    }
    return true;

}
