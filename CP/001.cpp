/* 
Consider an algorithm that takes as input a positive integer n. 
If n is even, the algorithm divides it by two, and if n is odd, the algorithm multiplies it by three and adds one. 
The algorithm repeats this, until n is one. For example, the sequence for n=3 is as follows: 
*/

#include <iostream>

using namespace std;

int main() {
    long long n;  // Use long long to prevent overflow
    cin >> n;

    while (n != 1) {
        cout << n << " ";
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;  // Ternary operator for clarity
    }
    
    cout << "1\n";  // Print final value outside the loop
    return 0;
}
