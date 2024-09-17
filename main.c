#include <stdint.h>
#include <stdio.h>

#define test_size 1145141919

uint64_t sxcstrlen_containzero(uint64_t x) {
    uint64_t x_lo = x & 0b0101010101010101010101010101010101010101010101010101010101010101;
    uint64_t x_hi = x & 0b1010101010101010101010101010101010101010101010101010101010101010;
    uint64_t x_2 = x_lo | (x_hi >> 1);
    uint64_t x_4 = x_2 | (x_2 >> 2);
    uint64_t x_8 = x_4 | (x_4 >> 4);
    return ((~x_8) & 0b0000000100000001000000010000000100000001000000010000000100000001);
}

uint32_t sxcstrlen(const char* str) {
    uint32_t n = 0;
    while (1) {
        if (sxcstrlen_containzero(*(uint64_t*)(str + n))) {
            break;
        } else {
            n += 8;
        }
    }
    for (uint32_t i = 0; i < 8; i++) {
        if (str[n + i] == 0) {
            return n + i;
        }
    }
}

int main() {
    static char test_str[test_size +1];
    for (uint32_t i = 0; i < test_size; i++) {
        test_str[i] = 'A';
    }
    test_str[test_size] = '\0';
    printf("%u\n", sxcstrlen(test_str));
    return 0;
}