#include <iostream>
#include <bitset>
#include <iomanip>

using namespace std;

/* Helper Function:: Bin >> dec */
void printBinary(const string& label, long long value, int bits = 32) {
    cout << left << setw(25) << label
         << bitset<32>(value) 
         << "  (decimal: " << value << ")\n";
}

int main() {
    cout << "[++ Signed, Unsigned & Two's Complement ++]\n\n";

    /* Signed Integers */
    cout << "1. SIGNED INTEGER (int)\n";
    cout << "   Can store positive and negative numbers.\n\n";

    int s1 = 5;
    int s2 = -5;
    int s3 = -1;

    printBinary("int  5 :", s1);
    printBinary("int -5 :", s2);
    printBinary("int -1 :", s3);

    cout << "\n";

    /* Unsigned Integers */
    cout << "2. UNSIGNED INTEGER (unsigned int)\n";
    cout << "   Can only store non-negative numbers (0 and positive).\n\n";

    unsigned int u1 = 5;
    unsigned int u2 = UINT_MAX;           // Maximum unsigned value

    printBinary("unsigned  5 :", u1);
    printBinary("unsigned MAX:", u2);

    cout << "\n";

    /* Two's complement */
    cout << "3. TWO'S COMPLEMENT REPRESENTATION\n";
    cout << "   How negative numbers are stored in memory.\n\n";

    uint32_t positive = 5;
    uint32_t inverted = ~positive;        // Flip all bits
    uint32_t twosComplement = inverted + 1;

    cout << "Example: Representing -5 in 32-bit:\n";
    cout << "   Positive 5     : " << bitset<32>(positive) << "\n";
    cout << "   Invert bits    : " << bitset<32>(inverted) << "\n";
    cout << "   Add 1          : " << bitset<32>(twosComplement) 
         << "  [>>] This is how -5 is actually stored\n\n";

    cout << "Note: Signed and unsigned use the same bit patterns.\n";
    cout << "      Only the interpretation changes.\n\n";

    /* diff */
    cout << "4. IMPORTANT DIFFERENCES\n\n";

    cout << "[+] Signed overflow   : Undefined behavior (dangerous)\n";
    cout << "[+] Unsigned overflow : Wraps around cleanly (defined)\n\n";

    int signedVal = INT_MAX;
    unsigned int unsignedVal = UINT_MAX;

    cout << "Signed max + 1  = " << (signedVal + 1) << "  (wraps to negative!)\n";
    cout << "Unsigned max + 1 = " << (unsignedVal + 1) << "  (becomes 0)\n";

    return 0;
}