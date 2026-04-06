#include <iostream>
#include <set>

int main() {
    int n = 0;
    std::cout << "Enter Set Size: ";
    std::cin >> n;

    std::set<int> arr;

    std::cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i) {
        int x {};
        std::cin >> x;
        arr.insert(x);
    }

    /* Original Set */
    std::cout << "[ ";
    for (const auto& x : arr) {
        std::cout << x << " ";
    }
    std::cout << "]\n";

    /* Increasing Order */
    std::cout << "Increasing Order -> [ ";
    for (const auto& z : arr) {
        std::cout << z << " ";
    }
    std::cout << "]\n";

    /* MULTISET */
    std::multiset<double> arr_2;
    arr_2.insert(5);
    arr_2.insert(4);
    arr_2.insert(5);
    arr_2.insert(3);

    std::cout << "MULTISET -> [ ";
    for (const auto& r : arr_2) {
        std::cout << r << " ";
    }
    std::cout << "]\n";

    return 0;
}