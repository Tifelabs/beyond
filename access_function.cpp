#include <iostream>

class Date{
    private:
        int m_year = 2026;
        int m_month = 4;
        int m_day = 11;

    public:
        void print()const{
            std::cout << m_year << "/" << m_month << "/" << m_day << "\n";
        }
};

int main(){
    Date d{};
    d.print();
    
    return 0;
}