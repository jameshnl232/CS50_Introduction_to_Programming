// Program to illustrate the getopt()
// function in C

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    int opt;

    // put ':' in the starting of the
    // string so that program can
    //distinguish between '?' and ':'
    while((opt = getopt(argc, argv, “:if:lrx”)) != -1)
    {
        switch(opt)
        {
            case ‘i’:
            case ‘l’:
            case ‘r’:
                printf(“option: %c\n”, opt);
                break;
            case ‘f’:
                printf(“filename: %s\n”, optarg);
                break;
            case ‘:’:
                printf(“option needs a value\n”);
                break;
            case ‘?’:
                printf(“unknown option: %c\n”, optopt);
                break;
        }
    }

    // optind is for the extra arguments
    // which are not parsed

    printf("optind ist %i\n", optind);

    for(; optind < argc; optind++){
        printf(“extra arguments: %s\n”, argv[optind]);
    }

    return 0;
}

//result:
// ./getopt.c -i -f filetext.txt -lr -x 'hero'

//option is: i
//filename: filename.txt
//option is: l
//option is: r
//unkown option: x   now getopt returns -1
// optind starts with 1, and by the time getopt returns -1, optind would be 6, while argc is 7
//extra arguments: hero   //by comparing optind < argc we can find the extra arguments

