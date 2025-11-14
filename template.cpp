#include <iostream>
#include <string>

template<typename N>

void Text(N *message){
    std::cout << message << '\n';
}

int main(void){

    Text("This application is depreciated\n");
    std::cin.get();
}