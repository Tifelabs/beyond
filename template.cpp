#include <iostream>
#include <string>

template <typename T>
T max(T x, T y){
    return (x > y) ? x : y;
}

template <typename T>
void Text(T *message){
    std::cout << message << '\n';
}

template <typename T>
void User(const T &name, const T &title){
    std::cout << "Name is " << name << " with " << title << "\n"; 
}

int main(void){
    Text<const char>("This application is depreciated\n");
    User<std::string>("Claire", "Phd");
    std::cout <<"The maximum value is -> " << max<int>(4, 8) << "\n";
    return 0;
}
