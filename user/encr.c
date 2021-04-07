#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user.h"
#include "openmodes.h"

char*
fmtname(char *path)
{
	static char buf[DIRSIZ+1];
	char *p;

	// Find first character after last slash.
	for(p=path+strlen(path); p >= path && *p != '/'; p--)
		;
	p++;

	// Return blank-padded name.
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	// memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
	return buf;
}

void
helpMenu(){
    printf("\nUse this program to encrypt files written on the disk.\n");
    printf("Usage: encr [OPTION]... [FILE]...\n\n");

    printf("Command line options:\n");
    printf("         -h, --help: Show help promt.\n");
    printf("         -a, --encrypt-all: Encrypt all files in CWD with current key.\n");
}


void
encrypt(char *file){
        int fd;

        if((fd = open(file, O_RDWR)) < 0){
			printf("cannot open %s\n", file);
			return;
		}

        switch(encr(fd)){
            case 0:
                printf("Successfully encrypted file: %s \n", file);
                break;
            case -1:
                printf("Failed to encrypt file: %s [key not set]\n", file);
                break;
            case -2:
                printf("Failed to encrypt file: %s [can't encrypt dev file]\n", file);
                break;
            case -3:
                printf("Failed to encrypt file: %s [file is already encrypted]\n", file);
                break;
            default:
                printf("Greska\n");
        }
        close(fd);
}

int
main(int argc, char *argv[])
{
    int fd, size, k, i, n = 150;
    struct stat st;
	struct dirent de;


    if(argc < 2){
        helpMenu();
        exit();
    }

    for(i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")){
            helpMenu();
            exit();
        }
        if(!strcmp(argv[i], "-a") || !strcmp(argv[i], "--encrypt-all")){
            // ceo dir
	        char buf[512], *p;

            if((fd = open(".", 0)) < 0){
                fprintf(2, "ls: cannot open %s\n", ".");
                return;
	        }
            if(fstat(fd, &st) < 0){
                fprintf(2, "ls: cannot stat %s\n", ".");
		        close(fd);
		        return;
            }
            strcpy(buf, ".");
            p = buf+strlen(buf);
            *p++ = '/';
            while(read(fd, &de, sizeof(de)) == sizeof(de)){ // direnti iz foldera
                if(de.inum == 0)
                    continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;

                encrypt(fmtname(buf));
			    // printf("%s\n", fmtname(buf));
		    }
            break;
        }
        encrypt(argv[i]);

    }



	exit(); // mora exit na kraju poziva
}
