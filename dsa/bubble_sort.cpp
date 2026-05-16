#include <iostream>
#include <vector>
#include <algorithm>


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n{};
    std::cin >> n;

    std::vector<int> arr(n);
    for(int i = 0; i < n; i++){
        std::cin >> arr[i];
    }

    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
        }
    }

    return 0;
}