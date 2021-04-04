#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "openmodes.h"


void
blockwriter(char *name, int blockNum){

}

int
main(int argc, char *argv[])
{
    int fd, size, k;

    k = atoi(argv[1]); // hvatam argument u komandnoj liniji
    k = 150;

    fd = open("long.txt", O_CREATE | O_RDWR); // file
    size=512;

    char niz[512] = "8arCLufFuKR5a9CDlIHvHNCvhMipyM0HD2GLX6q349NYW4IaZ9Xy67FtfRiegZu4V1yZ0hESKl22CEgItYkBmqIYJxIHonYm84fZnPloOGqIuh6gokrsOAqUuu2L3tNIv9MjIXQsfJsKfTrsRPBfzFICZnVr4egeEnQBFJdAGMXzQBQscgeQvIGowxH7EpLgBj5YsIUcMZ3byiW83Rf6HpZRs72Uv8FmwIwWaYbbGdFMHGSl5qAoFq5VPV2rB2CvAvYBkGJsLWEX8bhJSp1oJmNu0kdchO5SZLriwtNWdFVNomsAgEITwOEXqkHXgre3xJGkXCHQIAKbhPuHtIgn4KSCJSpgB3HY58mOSKIQGqWTPYhfuL1YtQ8jj9gT0GBWdkaFfSolUbDQDQLMzdsv3SHN108CAsMxBbXzEq1pzFevyUQFUuw3pIYJjpN6TyM3Oer6hukvQwncrBmDjkXa9NtW4ZtUOZEwE8PAerLEg9PeveMi3Iao7CBtE4gMxUUT";// niz od 32 * 16
    for(int i = 0; i < k; i++){
        printf("Writing block %d\n", i);
        if(write(fd, &niz, size) != size) {
            printf("write error\n");
        }
    }
	exit(); // mora exit na kraju poziva
}
