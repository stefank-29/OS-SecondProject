#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "openmodes.h"


int
main(int argc, char *argv[])
{
    int fd, size, k, i, n = 150;
    char* filename = "long.txt";

   // k = atoi(argv[1]); // hvatam argument u komandnoj liniji

    setkey(5);

	exit(); // mora exit na kraju poziva
}
