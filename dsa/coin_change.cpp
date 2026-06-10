#include <iostream>
#include <vector>
#include <climits>

// Returns the minimum number of coins to make 'amount'
// Returns -1 if it's not possible
int coinChange(const std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0; // base case: 0 coins needed to make amount 0

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int main() {
    std::vector<int> coins = {1, 5, 10, 25}; // quarter, dime, nickel, penny
    int amount = 41;

    int result = coinChange(coins, amount);

    if (result != -1)
        std::cout << "Minimum coins to make " << amount << ": " << result << "\n";
    else
        std::cout << "Cannot make amount " << amount << " with given coins.\n";

    return 0;
}