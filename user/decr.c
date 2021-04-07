#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "openmodes.h"

void
helpMenu(){
    printf("\nUse this program to decrypt files written on the disk.\n");
    printf("Usage: decr [OPTION]... [FILE]...\n\n");

    printf("Command line options:\n");
    printf("         -h, --help: Show help promt.\n");
    printf("         -a, --encrypt-all: Decrypt all files in CWD with current key.\n");
}


int
main(int argc, char *argv[])
{
    int fd, size, k, i, n = 150;


    if(argc < 2){
        helpMenu();
        exit();
    }

    for(i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")){
            helpMenu();
            exit();
        }
        if(!strcmp(argv[i], "-a") || !strcmp(argv[i], "--decrypt-all")){
            // ceo dir
        }
        if((fd = open(argv[i], O_RDWR)) < 0){
			printf("cannot open %s\n", argv[i]);
			exit();
		}


        switch(decr(fd)){
            case 0:
                printf("Successfully decrypted file: %s \n", argv[i]);
                break;
            case -1:
                printf("Failed to decrypt file: %s [key not set]\n", argv[i]);
                break;
            case -2:
                printf("Failed to decrypt file: %s [can't encrypt dev file]\n", argv[i]);
                break;
            case -3:
                printf("Failed to decrypt file: %s [file is not encrypted]\n", argv[i]);
                break;
            default:
                printf("Greska\n");
        }
        close(fd);
    }



	exit(); // mora exit na kraju poziva
}
