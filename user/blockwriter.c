#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "openmodes.h"

int
main(int argc, char *argv[])
{
    int k;
    int fd;

    // k = atoi(argv[1]); // hvatam argument u komandnoj liniji
    k = 150;

    fd = open("long.txt", O_CREATE | O_RDWR); // file

    char zvezda[7] = "Zvezda";
    for(int i = 0; i < k; i++){
        if(write(fd, &t, size) != size) {

        }
    }
	exit(); // mora exit na kraju poziva
}
