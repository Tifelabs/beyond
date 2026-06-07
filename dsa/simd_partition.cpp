#include <immintrin.h>
#include <cstdint>
#include <cstring>
#include <iostream>

// Partition 'n' floats into negatives (left) and non-negatives (right).
// Returns the index of the first non-negative element (the split point).
// 'n' must be a multiple of 8; input is modified in-place.
size_t simd_partition(float* data, size_t n) {
    float neg_buf[8], pos_buf[8];
    size_t neg_count = 0, pos_count = 0;

    // Temporary staging buffers (2 x 256-bit lanes worth)
    float neg_stage[n], pos_stage[n];

    const __m256 zero = _mm256_setzero_ps();

    for (size_t i = 0; i < n; i += 8) {
        __m256 v = _mm256_loadu_ps(&data[i]);

        // Mask: 0xFFFFFFFF where v < 0, 0x00000000 otherwise
        __m256 neg_mask = _mm256_cmp_ps(v, zero, _CMP_LT_OQ);

        // Compress matching lanes into contiguous arrays
        // (manual scatter since AVX2 lacks compress; AVX-512 has _mm256_mask_compressstoreu_ps)
        int mask = _mm256_movemask_ps(neg_mask); // 8-bit bitmask
        _mm256_storeu_ps(neg_buf, v);
        _mm256_storeu_ps(pos_buf, v);

        for (int j = 0; j < 8; j++) {
            if (mask & (1 << j))
                neg_stage[neg_count++] = neg_buf[j];
            else
                pos_stage[pos_count++] = pos_buf[j];
        }
    }

    // Write partitioned results back
    memcpy(data,             neg_stage, neg_count * sizeof(float));
    memcpy(data + neg_count, pos_stage, pos_count * sizeof(float));

    return neg_count; // split point
}

int main() {
    alignas(32) float data[] = {
        3.f, -1.f, -4.f, 1.f, 5.f, -9.f, 2.f, -6.f,
        7.f, -3.f,  0.f, 8.f, -2.f, 4.f, -5.f, 1.f
    };
    constexpr size_t N = sizeof(data) / sizeof(float);

    size_t split = simd_partition(data, N);

    std::cout << "Negatives (" << split << "): ";
    for (size_t i = 0; i < split; i++) std::cout << data[i] << " ";

    std::cout << "\nNon-negatives (" << N - split << "): ";
    for (size_t i = split; i < N; i++) std::cout << data[i] << " ";
    std::cout << "\n";
}
