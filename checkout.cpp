#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

struct Item {
    std::string name;
    double price;
};

class BreweryCheckout {
private:
    std::vector<Item> menu = {
        {"IPA", 6.50},
        {"Stout", 7.00},
        {"Lager", 5.50},
        {"Pale Ale", 6.00}
    };
    std::vector<Item> cart;
    double total = 0.0;

public:
    void displayMenu() {
        std::cout << "\n=== Brewery Checkout Terminal ===\n";
        std::cout << "Menu:\n";
        for (size_t i = 0; i < menu.size(); ++i) {
            std::cout << i + 1 << ". " << menu[i].name << " - $" 
                      << std::fixed << std::setprecision(2) << menu[i].price << "\n";
        }
        std::cout << "0. Checkout\n";
    }

    void addToCart(int choice) {
        if (choice > 0 && choice <= static_cast<int>(menu.size())) {
            cart.push_back(menu[choice - 1]);
            total += menu[choice - 1].price;
            std::cout << menu[choice - 1].name << " added to cart.\n";
        } else if (choice != 0) {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    void displayCart() {
        if (cart.empty()) {
            std::cout << "\nCart is empty.\n";
            return;
        }
        std::cout << "\nCart Contents:\n";
        for (const auto& item : cart) {
            std::cout << "- " << item.name << " ($" << std::fixed << std::setprecision(2) << item.price << ")\n";
        }
        std::cout << "Total: $" << std::fixed << std::setprecision(2) << total << "\n";
    }

    void checkout() {
        if (cart.empty()) {
            std::cout << "\nNothing to checkout.\n";
            return;
        }
        displayCart();
        std::cout << "\nProceeding to checkout...\n";
        std::cout << "Thank you for your purchase! Total paid: $" 
                  << std::fixed << std::setprecision(2) << total << "\n";
        cart.clear();
        total = 0.0;
    }
};

int main() {
    BreweryCheckout terminal;
    int choice;

    while (true) {
        terminal.displayMenu();
        std::cout << "\nEnter choice (0-" << terminal.menu.size() << "): ";
        std::cin >> choice;

        if (choice == 0) {
            terminal.checkout();
            if (terminal.cart.empty()) {
                std::cout << "Exiting terminal.\n";
                break;
            }
        } else {
            terminal.addToCart(choice);
            terminal.displayCart();
        }
    }

    return 0;
}