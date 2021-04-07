#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "openmodes.h"


void
blockwriter(char *name, int blockNum){
    int fd, size, k;

    fd = open(name, O_CREATE | O_RDWR); // file
    size=512;

    char niz[512] = "8arCLufFuKR5a9CDlIHvHNCvhMipyM0HD2GLX6q349NYW4IaZ9Xy67FtfRiegZu4V1yZ0hESKl22CEgItYkBmqIYJxIHonYm84fZnPloOGqIuh6gokrsOAqUuu2L3tNIv9MjIXQsfJsKfTrsRPBfzFICZnVr4egeEnQBFJdAGMXzQBQscgeQvIGowxH7EpLgBj5YsIUcMZ3byiW83Rf6HpZRs72Uv8FmwIwWaYbbGdFMHGSl5qAoFq5VPV2rB2CvAvYBkGJsLWEX8bhJSp1oJmNu0kdchO5SZLriwtNWdFVNomsAgEITwOEXqkHXgre3xJGkXCHQIAKbhPuHtIgn4KSCJSpgB3HY58mOSKIQGqWTPYhfuL1YtQ8jj9gT0GBWdkaFfSolUbDQDQLMzdsv3SHN108CAsMxBbXzEq1pzFevyUQFUuw3pIYJjpN6TyM3Oer6hukvQwncrBmDjkXa9NtW4ZtUOZEwE8PAerLEg9PeveMi3Iao7CBtE4gMxUUT";
    // char niz[512] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrst";
    for(int i = 0; i < blockNum; i++){
        printf("Writing block %d\n", i);
        if(write(fd, &niz, size) != size) {
            printf("write error\n");
        }
    }
}

int
main(int argc, char *argv[])
{
    int fd, size, k, i, n = 150;
    char* filename = "long.txt";

   // k = atoi(argv[1]); // hvatam argument u komandnoj liniji

    if(argc < 2){
        blockwriter("long.txt", 150);
        exit();
    }

    for(i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")){
            printf("\nUse this program to create a big file filled with a-z, A-Z and 0-9 characters.\n");
            printf("Default filename: long.txt\n");
            printf("Default blocks: 150\n");
            printf("Usage: blockwriter [OPTION]...\n\n");

            printf("Command line options:\n");
            printf("         -h, --help: Show help promt.\n");
            printf("         -b, --blocks: Number of blocks to write.\n");
            printf("         -o, --output-file: Set output filename.\n");
            exit();
        }
        if(!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output-file")){
           filename = argv[++i];
        }
        if(!strcmp(argv[i], "-b") || !strcmp(argv[i], "--blocks")){
            n = atoi(argv[++i]);
        }

    }

    blockwriter(filename, n);

	exit(); // mora exit na kraju poziva
}
