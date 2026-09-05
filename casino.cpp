#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <map>
#include <thread>
#include <fstream>

#define MINIMUM_WAGER 0.20

/* Function Prototypes */
double deposit(double balance, double amount);
double withdraw(double balance, double amount);
void wager(double amount);
void display(double& balance);

double deposit(double balance, double amount){
    if(amount < 50.0){
        std::cout << "Can't Deposit less than $50\n";
        return balance;
    }
    balance += amount;
    return balance;
}

double withdraw(double balance, double amount){
    if(amount > balance){
        std::cout << "Insufficient funds\n";
        return balance;
    }
    balance -= amount;
    return balance;
}

void changeUsername(){
    int option{};
    std::cout << "Select Operation\n";
    std::cout << "\t\t[1] Change Username";
    std::cout << "\t\t[2] Delete Username\n";

    switch (option)
    {
    case 1:
        std::cout << "Previous Username: \n";
        std::ifstream Rfile("username.txt");
        if(!Rfile == -1){
            std::cerr << "Error Opening File\n";
            return 1;
        }
         std::string name;
         while(std::getline(Rfile, name)){
            std::cout << name << "\n";
         }
         Rfile.close()

        }

        username();
        break;

    case 2:
        std::cout << "Are you Sure you want to delete username?\n"
        std::cout << "Enter [Y]es  [N]o \n";
        
        char opt;
        if(opt == 'Y'){
            std::cout << "Deleting Username\n";

        }else{
            std::cout << "Returining back to Menu\n";
            display();
        }
    
    default:
        break;
    }

}

void username(){
    std::string name;
    std::ofstream file("username.txt");
    std::cout << "Enter Username: \n";
    std::cin >> name;
    file << name;
    std::cout << "Username Registered Successfully\n";
    file.close();
}

void display(double& balance){
    bool running = true;
    while(running){
        std::cout << "\t CRYLESS CASINO \n\n";
        std::cout << "Enter an Option to Proceed [1 -7] \n";
        std::cout << "[1]\t Deposit Money\n";
        std::cout << "[2]\t Withdraw Money\n";
        std::cout << "[3]\t Check  Balance\n";
        std::cout << "[4]\t HEADS && TAILS\n";
        std::cout << "[5]\t High or Low\n";
        std::cout << "[6]\t Set Username\n";
        std::cout << "[7]\t Delete or Change Username\n";
        std::cout << "[8]\t Quit\n";

        int choice{};
        std::cin >> choice;
        std::cout << "\033[2J\033[1;1H";

        if(choice == 1){
            std::cout << "[++ DEPOSIT ++]\n";
            std::cout << "Enter amount to deposit [$50+]\n";
            double amount;
            std::cin >> amount;
            balance = deposit(balance, amount);
        }
        else if(choice == 2){
            std::cout << "[++ WITHDRAW ++]\n";
            std::cout << "Enter amount to withdraw\n";
            double amount;
            std::cin >> amount;
            balance = withdraw(balance, amount);
        }
        else if(choice == 3){
            std::cout << "Balance: $" << balance << "\n";
        }
        else if(choice == 6){
            username();
        }
        else if(choice == 8){
            running = false;
        }
    }
}

int main(){
    double balance = 0.0;
    display(balance);
}