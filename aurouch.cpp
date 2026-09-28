// Aurochs Cipher


#include <cstdint>
#include <vector>
#include <array>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>

class AurochsCipher {
public:
    static constexpr size_t LEN_A = 11;
    static constexpr size_t LEN_B = 13;
    static constexpr size_t LEN_C = 17;
    static constexpr size_t MIN_KEY = 16;
    static constexpr size_t MAX_KEY = 32;
    static constexpr size_t REC_KEY = 24;

    explicit AurochsCipher(const std::vector<uint8_t>& key) {
        if (key.size() < MIN_KEY || key.size() > MAX_KEY) {
            throw std::invalid_argument("Key must be 16-32 bytes");
        }
        init(key);
    }

    // Generate one keystream byte
    uint8_t next() {
        // Control value
        uint32_t sum = static_cast<uint32_t>(A[0]) + A[5] +
                       B[0] + B[6] +
                       C[0] + C[8];
        int r = static_cast<int>(sum % 7);

        // Always clock A
        clockRegister(A);

        // Conditional clocks
        if (r == 0 || r == 1 || r == 2 || r == 4) {
            clockRegister(B);
        }
        if (r == 1 || r == 3 || r == 5 || r == 6) {
            clockRegister(C);
        }

        // Output byte
        uint8_t z = A[3] ^ B[4] ^ C[7] ^
                    static_cast<uint8_t>((static_cast<uint32_t>(A[0]) + B[0]) & 0xFF);
        return z;
    }

    // Encrypt / decrypt (identical)
    std::vector<uint8_t> process(const std::vector<uint8_t>& data) {
        std::vector<uint8_t> out(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            out[i] = data[i] ^ next();
        }
        return out;
    }

    // Convenience for strings (treats as binary)
    std::string process(const std::string& data) {
        std::vector<uint8_t> bytes(data.begin(), data.end());
        auto result = process(bytes);
        return std::string(result.begin(), result.end());
    }

private:
    std::array<uint8_t, LEN_A> A{};
    std::array<uint8_t, LEN_B> B{};
    std::array<uint8_t, LEN_C> C{};

    void init(const std::vector<uint8_t>& key) {
        // Expand key to at least 41 bytes
        std::vector<uint8_t> K;
        K.reserve(64);
        while (K.size() < 41) {
            K.insert(K.end(), key.begin(), key.end());
        }
        // Simple fold if longer
        if (K.size() > 41) {
            for (size_t i = 41; i < K.size(); ++i) {
                K[i % 41] ^= K[i];
            }
            K.resize(41);
        }

        // Fill registers
        std::copy_n(K.begin(), LEN_A, A.begin());
        std::copy_n(K.begin() + LEN_A, LEN_B, B.begin());
        std::copy_n(K.begin() + LEN_A + LEN_B, LEN_C, C.begin());

        // Mix round
        for (size_t i = 0; i < 41; ++i) {
            uint8_t s = static_cast<uint8_t>(
                (static_cast<uint32_t>(A[i % LEN_A]) +
                 B[i % LEN_B] +
                 C[i % LEN_C]) & 0xFF);

            // Rotate left + XOR new rightmost
            rotateLeftXor(A, s);
            rotateLeftXor(B, s);
            rotateLeftXor(C, s);
        }
    }

    // Left rotate and XOR the new rightmost byte with value
    template <size_t N>
    static void rotateLeftXor(std::array<uint8_t, N>& reg, uint8_t val) {
        uint8_t first = reg[0];
        for (size_t i = 0; i < N - 1; ++i) {
            reg[i] = reg[i + 1];
        }
        reg[N - 1] = first ^ val;
    }

    // Clock a register: feedback = leftmost XOR mid XOR near-end, then shift left
    template <size_t N>
    static void clockRegister(std::array<uint8_t, N>& reg) {
        size_t mid = N / 2;
        size_t near = N - 3;
        uint8_t fb = reg[0] ^ reg[mid] ^ reg[near];

        for (size_t i = 0; i < N - 1; ++i) {
            reg[i] = reg[i + 1];
        }
        reg[N - 1] = fb;
    }
};

// ---------- Demo ----------
int main() {
    // Example 24-byte key
    std::vector<uint8_t> key = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
        0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x11, 0x22
    };

    AurochsCipher cipher(key);

    std::string plaintext = "Hello, obscure 