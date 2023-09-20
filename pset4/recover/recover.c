#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if( argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    if( file == NULL)
    {
        printf("Could not open\n");
        return 1;
    }


    typedef uint8_t BYTE;

    BYTE* Block = malloc(sizeof(BYTE)*512);
    if(Block == NULL)
    return 1;

    int i = 0;
    FILE* image;
    char JPEG[10];

    while( fread( Block, sizeof(Block), 1, file) )
    {

        if( *Block == 0xff && *(Block + 1) == 0xd8 && *(Block + 2) == 0xff && (*(Block + 3) & 0xf0) == 0xe0)
        {

            if ( i == 0)
            {
                sprintf(JPEG, "%03i.jpg", i);
                i++;

                image = fopen( JPEG, "w");

                if( image == NULL)
                return 1;

                fwrite( Block, sizeof(Block), 1, image );
            }

            else if ( i > 0)
            {

                fclose(image);

                sprintf(JPEG, "%03i.jpg", i);

                i++;

                image = fopen( JPEG, "w");
                if( image == NULL)
                return 1;

                fwrite( Block, sizeof(Block), 1, image );
            }
        }
        else if ( i > 0)
        {
            fwrite( Block, sizeof(Block), 1, image );
        }

    }

    fclose(image);
    fclose(file);
    free(Block);
    return 0;
}