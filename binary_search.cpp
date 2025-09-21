#include <iostream>
#include <vector>

// Binary search function: Returns index of target if found, else -1
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2; // Avoids overflow
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    std::vector<int> arr = {2, 4, 6, 8, 10, 12};
    int target = 8;
    int result = binarySearch(arr, target);
    if (result != -1)
        std::cout << "Element " << target << " found at index " << result << "\n";
    else
        std::cout << "Element " << target << " not found\n";
    return 0;
}