#include <iostream>

extern char **environ;

int main(int argc, char *argv[]){

    char **ep;

    for(ep = environ; *ep != NULL; ep++){
        std::cout << *ep << '\n';
        exit(0);
    }
    return 0;
}