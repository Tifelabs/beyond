#include <iostream>
#include <string>
#include <string_view>

class Employee {
    std::string m_name{};
    char m_firstInitial{};

public:
    void setName(std::string_view name){
        m_name = name;
        m_firstInitial = name.front(); 
    }

    void print() const{
        std::cout << "Employee " << m_name << " has first initial " << m_firstInitial << '\n';
    }
};

int main(){
    Employee e{};
    e.setName("Tina");
    e.print();

    e.setName("Randy");
    e.print();

    return 0;
}