#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using cd = std::complex<double>;
const double PI = acos(-1);

void fft(std::vector<cd>& a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    std::vector<cd> even(n / 2), odd(n / 2);
    for (int i = 0; i < n / 2; i++) {
        even[i] = a[i * 2];
        odd[i]  = a[i * 2 + 1];
    }

    fft(even, invert);
    fft(odd, invert);

    double angle = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(angle), sin(angle));

    for (int i = 0; i < n / 2; i++) {
        a[i]         = even[i] + w * odd[i];
        a[i + n / 2] = even[i] - w * odd[i];
        if (invert) {
            a[i]         /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

int main() {
   
    std::vector<cd> a = {1, 2, 3, 0};
    std::vector<cd> b = {1, 2, 0, 0};

    fft(a, false);
    fft(b, false);

    for (int i = 0; i < (int)a.size(); i++)
        a[i] *= b[i];

    fft(a, true);

    std::cout << "Result coefficients:\n";
    for (int i = 0; i < (int)a.size(); i++)
        std::cout << "x^" << i << ": " << (int)round(a[i].real()) << '\n';
}