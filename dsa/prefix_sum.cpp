#include <iostream>
#include <vector>

using ll = long long;

int main(){
    ll n{}, q{};
    std::cin >> n >> q;

    std::vector<ll> arr(n);
    std::vector<ll> prefix(n + 1, 0);

    for(ll i = 0; i < n; i++){
        std::cin >> arr[i];
    }

    for(ll i = 0; i < n; i++){
        prefix[i + 1] = prefix[i] + arr[i];
    }

    while(q--){
        ll a{}, b{};
        std::cin >> a >> b;
        std::cout << prefix[b] - prefix[a - 1] << "\n"; 
    }
    return 0;
}