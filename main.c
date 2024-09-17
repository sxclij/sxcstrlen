#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define test_size 1145141917
#define test_cnt 32

uint32_t sxcstrlen(const char* str) {
    uint32_t n = 0;
    while (1) {
        uint64_t x = (*(uint64_t*)(str + n));
        uint64_t x_lo = x & 0b0101010101010101010101010101010101010101010101010101010101010101;
        uint64_t x_hi = x & 0b1010101010101010101010101010101010101010101010101010101010101010;
        uint64_t x_2 = x_lo | (x_hi >> 1);
        uint64_t x_4 = x_2 | (x_2 >> 2);
        uint64_t x_8 = x_4 | (x_4 >> 4);
        if ((~x_8) & 0b0000000100000001000000010000000100000001000000010000000100000001) {
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
    static char test_str[test_size + 1];

    clock_t clock_start = clock();

    for (uint32_t i = 0; i < test_size; i++) {
        test_str[i] = 'a';
    }
    test_str[test_size] = '\0';

    for (uint32_t i = 0; i < test_cnt; i++) {
        printf("%u\n", sxcstrlen(test_str));
    }

    printf("time: %f\n", (clock() - clock_start) / (double)CLOCKS_PER_SEC);

    return 0;
}