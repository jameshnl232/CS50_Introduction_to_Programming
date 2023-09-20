#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //only one command-line argument
    if( argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    //make sure file could be opened
    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Can not open file.\n");
        return 1;
    }

    //allocate a buffer in memory
    BYTE *blockSize = malloc(sizeof(BYTE)*512);
    if(blockSize == NULL)
    {
        return 1;
    }

    //keep track of the number of file
    int i = 0;
    FILE *image;
    char buffer[10]; //this is for the name of a new jpeg

    while(fread(blockSize, sizeof(blockSize), 1, file))
    {
        if(blockSize[0] == 0xff && blockSize[1] == 0xd8 && blockSize[2] == 0xff &&
        (blockSize[3] & 0xf0) == 0xe0)
        {
            if( i == 0) //if this is the first jpeg
            {
                //create a name for the file

                sprintf(buffer, "%03i.jpg", 0);

                image = fopen(buffer, "w");
                if(image==NULL)
                {
                    return 1;
                }

                fwrite(blockSize, sizeof(blockSize), 1, image);
                i++; //update i
            }
            else if( i > 0) //if not the first jpeg
            {
                fclose(image);

                sprintf(buffer, "%03i.jpg", i);

                image = fopen(buffer, "w");
                if(image == NULL)
                {
                    return 1;
                }

                fwrite(blockSize, sizeof(blockSize), 1, image);
                i++;
            }

        }
        else if( i > 0) //if already found jpeg file
        {
            fwrite(blockSize, sizeof(blockSize), 1, image);
        }
    }

    //close file and free memory
    fclose(image);  //free should always be called last 
    fclose(file);
    free(blockSize);
    return 0;
}