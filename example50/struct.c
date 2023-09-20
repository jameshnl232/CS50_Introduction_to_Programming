#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    typedef struct
    {
        char* name;
        int note;
    }
    student;

    student Students[4];

    for(int i=0; i < 4; i++)
    {
        Students[i].name = get_string("Student %i: ", i +1);

        Students[i].note = get_int("Note %i: ", i + 1);
    }

    int Maxnote = 0;
    char* Beststudent;

    for(int i=0; i<4; i++)
    {
        if(Students[i].note > Maxnote)
        {
        Maxnote = Students[i].note;
        Beststudent = Students[i].name;
        }
    }

    printf("Maxnote: %i\n", Maxnote);

    printf("Best Student ist: %s\n", Beststudent);

    int number = get_int("number: ");

    if ( number > Maxnote)
    fprintf(stderr, "%i is higher than maxnote", number);

}
