#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    FILE *file = fopen("phonebook.csv", "a");

    char *name = get_string("name: ");
    char *number = get_string("number: ");
    
    if(file == NULL)
    return 1;

    fprintf(file, "%s\n%s\n", name, number);

    fclose(file);

}