#include <iostream>

namespace constant{
    constexpr double gravity {9.8};
}

double instantVelocity(int time, double gravity){
    return time * gravity;
}

int main(){

    std::cout << "Instant Velocity: " << instantVelocity(10, constant::gravity) << "\n";
    return 0;
}