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


std::map<std::string, std::string> Continents(){      
    return{
        {"NORTH AMERICA", "NA"},
        {"SOUTH AMERICA", "SA"},
        {"EUROPE", "EU"},
        {"AFRICA", "AF"},
        {"ASIA", "AS"},
        {"AUSTRALIA", "AU"},
        {"ANTARCTICA", "AN"}
        };
    }   

int main(){
    
    Details = &ShowDetails;
    Details();

    Account User = {"Zoe", "Tokyo", "AS", 22};
    std::cout << User.UserName << " is from " << User.City << '\n';

    auto regions = Continents();

    std::cout << "Name: " << User.UserName << '\n';
    std::cout << "City: " << User.City << '\n';
    std::cout << "Age: " << User.Age << '\n';
    std::cout << "Region: " << User.Region << '\n';
    std::cin.get();
    return 0;
}