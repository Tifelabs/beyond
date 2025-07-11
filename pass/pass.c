#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN 5

//Prototypes
void Hash();
void text();
void strength();
void Hash(){

}

void securityCheck(){
    printf("[*-*-*] Test pass security check with options \n");
    printf("\t[A] Check if pass is strong enough\n");
    printf("\t[B] Hash main password\n");

}

int main (int argc, char *argv[]){
    
    char buffer[8];

    printf("\t\t\t[--- PASS SECURITY ---]\n");

    while(1){
        printf("Enter a new Pass\n");
        scanf("%7d",buffer);
        if(strlen(buffer) < MIN){
            printf("[***]Pass must must be up to 6 - 8 characters !!");
        } else{
            securityCheck();
        }
    }

    return 0;
}
