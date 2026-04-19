#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/wait.h>

void prompt(){
    std::cout << " >  ";
}

int main(){
    std::cout << "Tiny Shell\n";

    std::string cmd;
    while(true){
    prompt();
    std::cin >> cmd;
    if(cmd == "exit") break;
    else if(cmd == "pid"){
        std::cout <<(int)getpid() << "\n";
    }
    else if(cmd == "fork"){
        int rc = fork();
        if(rc == 0){
            std::cout << "CHILD PROCESS PID ::" << (int)getpid() << "\n";
            sleep(2);
            std::cout << "Fork Successful\n";
            exit(0);
        } else {
            wait(NULL);
            std::cout << "PARENT PROCESS PID :: " << (int)getpid() << "\n";
             }
        }
    }
    return 0;
}