#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person
{
    char name[MAX_NAME];
    int age;
    struct person* next;
}
person;

person* hash_table[TABLE_SIZE];

unsigned int hash(char* name)
{
    unsigned int hash_value = 0;
    int length = strlen(name);
    for( int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }

    return hash_value;
}

void init_hash_table(void)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    return;
}

void print_table()
{
    printf("Start");
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if( hash_table[i] == NULL)
        {
            printf("\t%i\t--\n", i);
        }
        else
        printf("\t%i\t%s\n",i, hash_table[i]->name);
    }
    printf("End\n");
}
//insert a person into table using linked list
bool hash_table_insert( person* p)
{
    if (p == NULL) return false;
    int index = hash(p->name);
    
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

//find a person in table by name
person* hash_table_lookup (char* name)
{
    int index = hash(name);
    person* tmp = hash_table[index];
    while( tmp != NULL && strcmp(tmp->name, name) != 0)
    {
        tmp = tmp->next;
    }
    return tmp;
}
// delete a person in table
person* hash_table_delete (char* name)
{
    int index = hash(name);
    if (hash_table[index] != NULL && strcmp(hash_table[index]->name , name) == 0)
    {
        person* tmp = hash_table[index];
        hash_table[index] = NULL;
        return tmp;
    }
    else
    return NULL;
}

int main(void)
{
    init_hash_table();

    person Jacob = {.name="Jacob", .age=256};
    person Natalie = {.name="Natalie", .age=27};
    person Bill = {.name="Bill", .age=70};
    person Sara = {.name="Sara", .age=156};
    person Vera = {.name="vera", .age=20};

    hash_table_insert(&Jacob);
    hash_table_insert(&Natalie);
    hash_table_insert(&Bill);
    hash_table_insert(&Sara);
    hash_table_insert(&Vera);
    print_table();

    person* tmp = hash_table_lookup("Mpho");
    if( tmp == NULL)
    printf("not found %s\n", tmp->name);

    else
    printf("found %s\n", tmp->name);

    hash_table_delete("Sara");
    tmp = hash_table_lookup("Sara");
    if( tmp == NULL)
    printf("not found %s\n", tmp ->name);

    else
    printf("found %s\n", tmp->name);

    // /* to boi den ca doan ben duoi */

    /*printf("Jacob => %i\n", hash("Jacob"));
    printf("Natalie => %i\n", hash("Natalie"));
    printf("Sara => %i\n", hash("Sara"));
    printf("Ron=> %i\n", hash("Ron"));
    printf("Emil => %i\n", hash("Emil"));
    printf("Bill => %i\n", hash("Bill"));*/

    return 0;
}

