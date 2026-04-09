#include <iostream>
#include <vector>

using ll = long long;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    ll n{};
    std::cin >> n;
    std::vector<ll> arr(n);
    for(ll i = 0; i < n; i++){
        std::cin >> arr[i];
    }    

    for(ll i = n - 1; i >= 0; i--){
        std::cout << arr[i];
    }
    std::cout << "\n";
    return 0;
}