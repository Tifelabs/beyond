#include <iostream>
#include <string>
#include <map>

void (*Details)();

void ShowDetails(){
    std::cout << "\t\t\t[+_+_+_+ ACCOUNT DETAILS +_+_+_+]\n\n";
}

typedef struct Account{
    std::string UserName;
    std::string City;
    std::string Region;
    int Age;
} Account;

enum class Continent{
    NORTH_AMERICA,
    SOUTH_AMERICA,
    ASIA,
    AFRICA,
    ANTARCTICA,
    EUROPE,
    AUSTRALIA,
};

std::string GetContinent(Continent Code){
    switch(Code){
        case Continent::NORTH_AMERICA: return "NA";
        case Continent::SOUTH_AMERICA: return "SA";
        case Continent::ASIA: return "AS";
        case Continent::AFRICA: return "AF";
        case Continent::ANTARCTICA: return "AN";
        case Continent::EUROPE: return "EU";
        case Continent::AUSTRALIA: return "AU";
    };
}

int main(){
    
    Details = &ShowDetails;
    Details();

    Account User = {"Zoe", "Tokyo", "AS", 22};
    std::cout << User.UserName << " is from " << User.City << '\n';

    auto regions = Continent();

    std::cout << "Name: " << User.UserName << '\n';
    std::cout << "City: " << User.City << '\n';
    std::cout << "Age: " << User.Age << '\n';
    std::cout << "Region: " << User.Region << '\n';
    std::cin.get();
    return 0;
}