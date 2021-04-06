#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "openmodes.h"

void
helpMenu(){
    printf("\nUse this program to encrypt files written on the disk.\n");
    printf("Usage: encr [OPTION]... [FILE]...\n\n");

    printf("Command line options:\n");
    printf("         -h, --help: Show help promt.\n");
    printf("         -a, --encrypt-all: Encrypt all files in CWD with current key.\n");
}


int
main(int argc, char *argv[])
{
    int fd, size, k, i, n = 150;
    char* filename = "long.txt";

   // k = atoi(argv[1]); // hvatam argument u komandnoj liniji

    if(argc < 2){
        helpMenu();
        exit();
    }

    for(i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")){
            helpMenu();
            exit();
        }
        if(!strcmp(argv[i], "-o") || !strcmp(argv[i], "--encrypt-all")){
            // ceo dir
        }
        if((fd = open(argv[i], 0)) < 0){
			printf("cat: cannot open %s\n", argv[i]);
			exit();
		}


        switch(encr(fd)){
            case 0:
                printf("Successfully encrypted file: %s \n", argv[i]);
                break;
            case -1:
                printf("Failed to encrypt file: %s [key not set]\n", argv[i]);
                break;
            case -2:
                printf("Failed to encrypt file: %s [can't encrypt dev file]\n", argv[i]);
                break;
            case -3:
                printf("Failed to encrypt file: %s [file is already encrypted]\n", argv[i]);
                break;
        }
        close(fd);
    }



	exit(); // mora exit na kraju poziva
}
