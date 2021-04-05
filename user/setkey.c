#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "openmodes.h"


int
main(int argc, char *argv[])
{
    int fd, n, i;
    char *number;

   // k = atoi(argv[1]); // hvatam argument u komandnoj liniji

     for(i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")){
            printf("\nUse this program to set the current active key.\n");
            printf("After setting the key, you can use encr and decr with that key.\n");
            printf("Usage: setkey [OPTION]... [KEY]\n\n");

            printf("Command line options:\n");
            printf("         -h, --help: Show help promt.\n");
            printf("         -s, --secret: Enter the key via STDIN. Hide key when entering it.\n");
            exit();
        }
        if(!strcmp(argv[i], "-s") || !strcmp(argv[i], "--secret")){
           // iskljuciti echo
            printf("Enter the key: ");
            gets(number, 10);
            n = atoi(number);
            printf("%d", n);
            exit();
        }


    }

    setkey(n);

	exit(); // mora exit na kraju poziva
}
