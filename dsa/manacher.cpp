#include <bits/stdc++.h>
using namespace std;

/* Manacher's Algorithm */
// Returns the longest palindromic substring of s
string longestPalindrome(const string& s) {
    if (s.empty()) return "";

    // Transform: insert '#' between every character + sentinels
    // Example: "aba" → "^#a#b#a#$"
    string t = "^";
    for (char c : s) {
        t += '#';
        t += c;
    }
    t += "#$";

    int n = t.size();
    vector<int> p(n, 0);          // p[i] = radius of palindrome centered at i
    int center = 0, right = 0;    // current rightmost palindrome

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * center - i;   // mirror of i with respect to center

        // If i is inside the current rightmost palindrome, we can reuse info
        if (i < right)
            p[i] = min(right - i, p[mirror]);

        // Expand around i as far as possible
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]])
            ++p[i];

        // Update the rightmost palindrome if we expanded past it
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }

    // Find the maximum radius and its center
    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }

    // Extract the original substring
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

// -------------------- Example --------------------
int main() {
    vector<string> tests = {
        "babad",
        "cbbd",
        "a",
        "ac",
        "racecar",
        "abacdfgdcaba",
        "forgeeksskeegfor"
    };

    for (const string& s : tests) {
        cout << "\"" << s << "\" → \"" << longestPalindrome(s) << "\"\n";
    }
}