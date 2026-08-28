#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <map>
#include <thread>
#include <fstream>


#define MINIMUM_WAGER 0.20


/* Function Prototypes */
double deposit(double amount);
void withdraw(double amount);
void wager(double amount);
void display();

double deposit(double amount){
    std::cout<< "Enter amount to deposit [$50+]\n";
    if(amount < 50.0){
        std::cout << "Can't Deposit less than $50\n";
    }
    double balance = 0;
    balance += amount;
}

void display(){
    std::cout << "\t CRYLESS CASINO \n\n";
    std::cout << "Enter an Option to Proceed [1 -7] \n";
        std::cout << "[1]\t Deposit Money\n";
        std::cout << "[2]\t Withdraw Money\n";
        std::cout << "[3]\t Check  Balance\n";
        std::cout << "[4]\t HEADS && TAILS\n";
        std::cout << "[5]\t High or Low\n";
        std::cout << "[6]\t Set Username\n";
        std::cout << "[7]\t Quit\n";

        int choice{};
        std::cin >> choice;
        std::cout << "\033[2J\033[1;1H";

        if(choice == 1){
            std::cout << "[++ DEPOSIT ++]\n";
            deposit();
        }
}



int main(){
    display();
}