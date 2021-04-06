#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "openmodes.h"

int
isNumber(const char *s){
    while(*s != '\0'){

        if (!('0' <= *s && *s <= '9')){
            return 0;
        }
        *s++;
    }
    return 1;
}

int
main(int argc, char *argv[])
{
    int fd, n, i, error;
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
            setecho(0);
            number = gets(number, 10);
            n = atoi(number);
            setecho(1);
            break;
        }
        if(isNumber(argv[i])){
            n = atoi(argv[i]);
        }else{
            printf("Please enter an integer value.\n");
            exit();
        }
    }

    if(setkey(n) < 0){
        printf("System call error.\n");
    }

	exit(); // mora exit na kraju poziva
}
