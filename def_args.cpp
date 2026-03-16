#include <iostream>
#include <string>

void User(std::string name, std::string role = "admin"){
    std::cout << "NAME: " << name << " " << "ROLE: " << role << "\n";
}

int main(){
    User("Grace", "FBI");
    User("Leon");
    return 0;
}