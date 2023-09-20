#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check_valid( string key);

int main(int argc, string argv[])
{
    //count the key
    if( argc != 2 )
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check validity of the key
    if(!check_valid(argv[1]))
    {
        printf("Wrong key!\n");
        return 1;
    }

    //prompt for plaintext
    string plaintext = get_string("plaintext:  ");

    //make the letters correspond with each other
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    string  key = argv[1];

    for(int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if(!isalpha(plaintext[i]))
        {
            plaintext[i] = plaintext[i];
        }

        else if(isalpha(plaintext[i]))
        {
            for(int j = 0, m = strlen(alphabet); j < m; j++)
            {
                if(isupper(plaintext[i]) && tolower(plaintext[i]) == alphabet[j])
                {
                    plaintext[i] = toupper(key[j]);
                    break;
                }
                else if( islower(plaintext[i]) && plaintext[i] == alphabet[j] )
                {
                    plaintext[i] = tolower(key[j]);
                    break;
                }
            }
            //case sensitive
        }

    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}

bool check_valid( string key)
{
    if( strlen(key) != 26 )
    {
        return false;
    }

    for(int i = 0, n = strlen(key); i < n; i++)
    {
        if(!isalpha(key[i]))
        {
            return false;
        }
    }

    for(int i = 0, n = strlen(key); i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(key[i] == key[j])
            {
                return false;
            }
        }
    }
    return true;
}