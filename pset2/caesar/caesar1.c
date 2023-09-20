#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string key);
int rotate(int letter, int key);

int main(int argc, string argv[])
{
    if(argc != 2 || !only_digits(argv[1])) // count the command line arguments
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //prompt input
    string plaintext = get_string("Plaintext:  ");

    //rotate the plaintext to ciphertext
    for(int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if(isalpha(plaintext[i]) && isupper(plaintext[i]))
        {
            //minus 65 sothat A=0, B=1,...
            plaintext[i] = rotate((int)plaintext[i] - 65, atoi(argv[1])) + 65;
        }
        else if(isalpha(plaintext[i]) && islower(plaintext[i]))
        {
            plaintext[i] = rotate((int)plaintext[i] - 97, atoi(argv[1])) + 97;
        }
        else if(!isalpha(plaintext[i]))
        {
            plaintext[i] = plaintext[i];
        }
    }

    printf("Ciphertext: %s\n", plaintext);
    return 0;
}


bool only_digits(string key)
{
    for(int i = 0, n = strlen(key); i < n; i++)
    {
        if(!isdigit(key[i]))
        return false;
    }
    return true;
}

int rotate(int letter, int key)
{
    letter = (letter + key)%26;
    return letter;
}