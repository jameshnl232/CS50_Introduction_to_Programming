#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if ( score1 > score2 )
    {
        printf("Player1 wins!\n");
    }

    else if ( score2 > score1 )
    {
        printf("Player2 wins!\n");
    }

    else
    printf("Tie!\n");
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    int x;

    for( int i = 0, n = strlen(word); i<n; i++)
    {
        if ( 'a' <= word[i] && word[i] <= 'z')
        {
            word[i] =  (int) word[i] - 32;

            x = (int) word[i] - 65;

            score += POINTS[x];
        }

        if ( 'A' <= word[i] && word[i] <= 'Z')
        {
            word[i] = (int) word[i] + 32;

            x = (int) word[i] - 97;

            score += POINTS[x];
        }

        else
        {
            score = 0;
        }

    }
    return score;
}