// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

//word counter
int word_counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node* tmp = table[index];
    //loop for looking
    while( tmp != NULL )
    {
        if(strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) //https://joseph28robinson.medium.com/cs50-pset-5-speller-f9c89d08237e
{
    unsigned int hash_value = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        hash_value += tolower(word[i]);

    }
    return hash_value % N;
}
//initiate hash table
void init_hash_table(void)
{
    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    return;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE* file = fopen(dictionary, "r");
    if( file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    //initiate the hash_table
    init_hash_table();

    char word[LENGTH + 1];
    while( fscanf(file, "%s", word) != EOF)
    {
        node* tmp = malloc(sizeof(node));
        if( tmp == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(tmp->word, word);

        int index = hash(tmp->word);

        tmp->next = table[index];
        table[index] = tmp;

        word_counter++;
    }

    fclose(file); //co fopen phai co fclose
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node* cursor = table[i];

        while( cursor != NULL)
        {
            node* tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }

        if(i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
