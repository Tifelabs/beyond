#include <iostream>
#include <vector>

int main(){
    int n{}, target{};
    std::cout << "Enter array size and target: ";
    std::cin >> n >> target;

    std::vector<int> arr(n);
    for(int i = 0; i < n; i++){
        std::cin >> arr[i];
    }

    std::cout << "[";
    for(int i = 0; i < n; i++){
        std::cout << arr[i];
        if(i < n - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    int low{}, high = n - 1, ans = -1;

    while(low <= high){
        int mid = low + (high - low) / 2;
        if(arr[mid] == target){
            ans = mid;
            break;              
        } else if(arr[mid] < target){
            low = mid + 1;      
        } else {
            high = mid - 1;    
        }
    }
    std::cout << ans << '\n';
    return 0;
}