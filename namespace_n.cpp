#include <iostream>
#include <string>
#include <vector>

namespace Shopping {

    float getBudget() {
        return 1000.00f;
    }

    namespace Groceries {
        const std::vector<std::pair<int, std::string>> items = {
            {1, "Apple"}, {2, "Fish"},  {3, "Beef"},
            {4, "Rice"},  {5, "Vegetables"}
        };

        void printList() {
            for (const auto& item : items) {
                std::cout << item.first << ". " << item.second << "\n";
            }
        }
    }

    namespace Toiletries {
        const std::vector<std::pair<int, std::string>> items = {
            {1, "Brush"}, {2, "Deodorant"}, {3, "Mop"},
            {4, "Soap"},  {5, "Sanitizer"}
        };

        void printList() {
            for (const auto& item : items) {
                std::cout << item.first << ". " << item.second << "\n";
            }
        }
    }
}

int main() {
    std::cout << "Budget: $" << Shopping::getBudget() << "\n\n";

    std::cout << "[ GROCERIES ]\n";
    Shopping::Groceries::printList();

    std::cout << "\n[ TOILETRIES ]\n";
    Shopping::Toiletries::printList();

    return 0;
}