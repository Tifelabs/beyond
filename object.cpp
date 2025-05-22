#include <iostream>

void welcomeMsg(){
    std::cout<<"[WELCOME TO THE LEARNING PHASE]\n";
}

void selectEng(){
    std::cout<<"[1] Unreal Engine\n";
    std::cout<<"[2] Godot\n";
    std::cout<<"[3] Game Maker\n";
    std::cout<<"[4] Unity\n";
}


int select(){
    int choice;
    std::cin >> choice;

    if(choice == 1){
        std::cout<<"Loading Unreal!!!\n";
    }
    if (choice == 2){
        std::cout<<"Loading Godot!!!\n";
    }
    if (choice == 3){
        std::cout<<"Loading Gamee Maker!!!\n";
    }
    if (choice == 4){
        std::cout<<"Loading Unity!!!\n";
    }
    else{
        std::cout<<"ERRROR!!!!";
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]){
    
    welcomeMsg();
    std::cout<<"Select Engine Choice\n";
    selectEng();
    select();

    return 0;
}