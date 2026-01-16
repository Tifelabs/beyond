#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[]){
    char **ep;

    for(ep = environ; *ep != NULL; ep++){
        puts(*ep);
        exit(0);
    }
    return 0;
}