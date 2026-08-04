#include <cstdint>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

using u64 = uint64_t;
using u128 = __uint128_t;

u64 mod_pow(u64 base, u64 exp, u64 mod) {
    if (mod == 1) return 0;
    u128 result = 1;
    u128 b = base % mod;
    while (exp > 0) {
        if (exp & 1) result = (result * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return static_cast<u64>(result);
}

int64_t ext_gcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int64_t x1, y1;
    int64_t g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

u64 mod_inverse(u64 a, u64 m) {
    int64_t x, y;
    int64_t g = ext_gcd(static_cast<int64_t>(a), static_cast<int64_t>(m), x, y);
    if (g != 1) throw std::runtime_error("modular inverse does not exist");
    int64_t result = x % static_cast<int64_t>(m);
    if (result < 0) result += m;
    return static_cast<u64>(result);
}

bool is_prime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }

    u64 d = n - 1;
    int r = 0;
    while (d % 2 == 0) { d /= 2; r++; }

    auto witness = [&](u64 a) {
        u64 x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) return true;
        for (int i = 0; i < r - 1; i++) {
            x = static_cast<u64>((u128)x * x % n);
            if (x == n - 1) return true;
        }
        return false;
    };

    for (u64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= n) continue;
        if (!witness(a)) return false;
    }
    return true;
}

u64 generate_prime(int bits, std::mt19937_64& rng) {
    std::uniform_int_distribution<u64> dist(
        (u64)1 << (bits - 1), ((u64)1 << bits) - 1);
    while (true) {
        u64 candidate = dist(rng) | 1;
        if (is_prime(candidate)) return candidate;
    }
}

struct PublicKey  { u64 n, e; };
struct PrivateKey { u64 n, d; };
struct KeyPair { PublicKey pub; PrivateKey priv; };

KeyPair generate_keypair(int prime_bits = 16) {
    std::random_device rd;
    std::mt19937_64 rng(rd());

    u64 p = generate_prime(prime_bits, rng);
    u64 q = generate_prime(prime_bits, rng);
    while (q == p) q = generate_prime(prime_bits, rng);

    u64 n = p * q;
    u64 phi = (p - 1) * (q - 1);

    u64 e = 65537;
    if (e >= phi) e = 17;
    int64_t x, y;
    while (ext_gcd(static_cast<int64_t>(e), static_cast<int64_t>(phi), x, y) != 1) {
        e += 2;
    }

    u64 d = mod_inverse(e, phi);
    return { {n, e}, {n, d} };
}

u64 rsa_encrypt(u64 message, const PublicKey& pub) {
    if (message >= pub.n) throw std::runtime_error("message too large for key size");
    return mod_pow(message, pub.e, pub.n);
}

u64 rsa_decrypt(u64 ciphertext, const PrivateKey& priv) {
    return mod_pow(ciphertext, priv.d, priv.n);
}

std::vector<u64> rsa_encrypt_string(const std::string& msg, const PublicKey& pub) {
    std::vector<u64> out;
    out.reserve(msg.size());
    for (unsigned char c : msg) out.push_back(rsa_encrypt(c, pub));
    return out;
}

std::string rsa_decrypt_string(const std::vector<u64>& cipher, const PrivateKey& priv) {
    std::string out;
    out.reserve(cipher.size());
    for (u64 c : cipher) out.push_back(static_cast<char>(rsa_decrypt(c, priv)));
    return out;
}

int main() {
    KeyPair keys = generate_keypair(16);

    std::cout << "Public key:  (n=" << keys.pub.n  << ", e=" << keys.pub.e  << ")\n";
    std::cout << "Private key: (n=" << keys.priv.n << ", d=" << keys.priv.d << ")\n\n";

    std::string message = "Hello, RSA!";
    std::cout << "Original message: " << message << "\n";

    auto ciphertext = rsa_encrypt_string(message, keys.pub);
    std::cout << "Ciphertext: ";
    for (u64 c : ciphertext) std::cout << c << ' ';
    std::cout << "\n";

    std::string decrypted = rsa_decrypt_string(ciphertext, keys.priv);
    std::cout << "Decrypted message: " << decrypted << "\n";

    std::cout << (decrypted == message ? "\nRound-trip successful\n" : "\nRound-trip FAILED\n");
    return 0;
}