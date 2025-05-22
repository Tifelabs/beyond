#include <iostream>
#include <cstring>
#include <string>

class Plane {
    public:
        int Speed;
        std::string Name;
        std::string Brand;
        std::string Country;
};

int main(int argc, char* argv[]){
    Plane myAviation;               //Creating an object of Plane

    //Accessing attr and setting values
    myAviation.Speed = 145;
    myAviation.Name = "F35";
    myAviation.Brand = "Fighter";
    myAviation.Country = "USA";

    std::cout <<"The Average Speed of an " << myAviation.Name <<" "<< myAviation.Brand << " is" << " " << myAviation.Speed <<'\n';
    std::cout <<"Made in " << myAviation.Country <<'\n';

    return 0;
}