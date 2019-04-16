#include "lab10_c_functions.h"


// Count the number of binary 1's using Algorithm 1
uint32_t C_number_of_1s_alg1(uint32_t x) {
    uint32_t n_of_1 = 0;            // number of 1s of the input
    while (x) {
        n_of_1 += x >> 31;
        x = x << 1;
    }
    return n_of_1;
}


// Count the number of binary 1's using Algorithm 2
uint32_t C_number_of_1s_alg2(uint32_t x) {
    uint32_t y, z;
    uint32_t n_of_1 = x >> 31;      // number of 1s of the input
    while (x) {
        y = x << 2;
        z = y >> 31;
        if (x<<1 > y)
            n_of_1 += z + 1;
        else
            n_of_1 += z;
        x = y;
    }
    return n_of_1;
}


// Count the number of binary 1's using Algorithm 3
uint32_t C_number_of_1s_alg3(uint32_t x) {
    uint32_t n_of_1 = 0;            // number of 1s of the input
    while (x) {
        x = x & (x-1);
        n_of_1++;
    }
    return n_of_1;
}
