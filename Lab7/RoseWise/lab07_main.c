#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define INITIALIZE_vals \
                a = 8;\
                x = 1;

#define INITIALIZE_OUTPUT_ARRAY \
    po = outpt_array; \
    for (i = 0; i < 8; i++) { \
        *(po + i) = 0; \
    }\

// Functions defined in a .s file
extern uint32_t task1(uint32_t a, uint32_t x);
extern uint32_t task2(uint32_t a, uint32_t x);
extern uint32_t task3(uint32_t a, uint32_t x);
extern uint32_t task4(uint32_t a, uint32_t x);
extern uint32_t task5(uint32_t n);
extern uint32_t task6(uint32_t *ptr, uint32_t n);
extern uint32_t task7(uint32_t n);
extern uint32_t task8(uint32_t *ptr, uint32_t n);
extern uint32_t task9(uint32_t n);
extern uint32_t task10(uint32_t *ptr, uint32_t n);

    
// Global variable

uint32_t a, x;

uint32_t input_array[8] = {11, 12, 13, 14, 15, 16, 17, 18};
uint32_t outpt_array[8] = {1, 2, 3, 4, 5, 6, 7, 8};
uint32_t i, sum5, sum6, sum7, sum8, sum9, sum10;


int main(void) {
// Task 1. Simple if-then statement:
    INITIALIZE_vals
    printf("a_1a = %u\n", a);
    if (a > x) {
        a >>= 2;
        a++;
    }
    printf("a_1b = %u\n", a);
    INITIALIZE_vals
    a = task1(a, x);
    printf("a_1c = %u\n", a);

// Task 2. Simple if-then statement with compound logic OR expression:
    INITIALIZE_vals
    printf("a_2a = %u\n", a);
    if (x <= 20 || x >= 25) {
        a *= 2;
        a--;
    } 
    printf("a_2b = %u\n", a);
    INITIALIZE_vals
    a = task2(a, x);
    printf("a_2c = %u\n", a);
    
// Task 3. Simple if-then-else statement:
    INITIALIZE_vals
    if (a == 8*x) {
        x -= 10;
    } else {
        x -= 4;
    }
    printf("xi_3a = %i, xu_3a = %u\n", x, x);
    INITIALIZE_vals
    x = task3(a, x);
    printf("xi_3b = %i, xu_3b = %u\n", x, x);
    
// Task 4. If-then-else statement with compound logic OR expression:
    INITIALIZE_vals
    printf("a_4a = %u\n", a);
    if (x <= 20 || x >= 25) {
        a++;
        a *= 8;
    } else {
        a--;
        a *= 16;
    }
    printf("a_4b = %u\n", a);
    INITIALIZE_vals
    a = task4(a, x);
    printf("a_4c = %u\n", a);


// Task 5. The for loop
    uint32_t n = 10;
    sum5 = 0;
    for (i = 0; i < n; i++) {
        sum5 += (i+2)*8;
    }
    printf("sum5_a = %u\n", sum5);
    sum5 = 0;
    sum5 = task5(n);
    printf("sum5_b = %u\n", sum5);

// Task 6. The for loop---revisit the addressing problem
    uint32_t *pArray = input_array;
    n = 8;
    sum6 = 0;
    for (i = 0; i < n; i++) {
        sum6 += *pArray++ & 0x0F;
    }
    printf("sum6_a = %u\n", sum6);
    sum6 = 0;
    pArray = input_array;
    sum6 = task6(pArray, n);
    printf("sum6_b = %u\n", sum6);

// Task 7. A while loop.
    n = 10;
    i = 0;
    sum7 = 0;
    while (i < n) {
        sum7 += i*4 | 0x0F;
        i++;
    }
    printf("sum7_a = %u\n", sum7);
    sum7 = 0;
    sum7 = task7(n);
    printf("sum7_b = %u\n", sum7);

// Task 8. Another while loop 
    pArray = input_array;
    n = 6;
    i = n;
    sum8 = 0;
    while (i > 0) {
        i--;
        sum8 += *(pArray + i);
    }
    printf("sum8_a = %u\n", sum8);
    sum8 = 0;
    sum8 = task8(pArray, n);
    printf("sum8_b = %u\n", sum8);

// Task 9. A do-while loop 
    n = 10;
    i = 0;
    sum9 = 0;
    do {
        sum9 += i*4 | 0x0F;
        i++;
    } while (i < n);
    
    printf("sum9_a = %u\n", sum9);
    sum9 = 0;
    sum9 = task9(n);
    printf("sum9_b = %u\n", sum9);

// Task 10. Another do-while loop 
    pArray = input_array;
    n = 6;
    i = n;
    sum10 = 0;
    while (i > 0) {
        sum10 += 2 * *pArray++;
        i--;
    }
    printf("sum10_a = %u\n", sum10);
    pArray = input_array;
    sum10 = 0;
    sum10 = task10(pArray, n);
    printf("sum10_b = %u\n", sum10);
    
    while (1);
}
