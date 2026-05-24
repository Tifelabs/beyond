#include <iostream>
#include <vector>

// Heapify a subtree rooted at index i
// n = size of the heap
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;       // Assume root is largest
    int left    = 2*i + 1; // Left child
    int right   = 2*i + 2; // Right child

    // If left child exists and is greater than current largest
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child exists and is greater than current largest
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not the root, swap and continue heapifying
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // Phase 1: Build a max-heap from the array
    // Start from the last non-leaf node and heapify upward
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Phase 2: Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (max) to the end
        std::swap(arr[0], arr[i]);

        // Heapify the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    std::cout << "Before: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";

    heapSort(arr);

    std::cout << "After:  ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
