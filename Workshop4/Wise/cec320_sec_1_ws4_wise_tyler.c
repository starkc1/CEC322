#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

extern void aTask1(int32_t *arr1, int32_t *arr2, int32_t *arr3, uint32_t M);
extern void aTask2(int32_t *arr1, int32_t *arr2, int32_t *arr3, uint32_t M_n);
extern void aTask3(int32_t *arr1, int32_t *arr2, int32_t *arr3, uint32_t M_n);
extern void aTask4(int32_t *arr1, int32_t *arr2, int32_t *arr3, uint32_t M_n);

// Global variable
#define M 8         // The size of the arrays
uint32_t n = 8;     // The n in Qm.n format
float real_array1[M] = {11.1, -12.2, 13.3, 14.4, 15.5, 16.6, 17.7, 18.8};
float real_array2[M] = {1.1, 2.2, 3.3, -4.4, 5.5, 6.6, 7.7, 8.8};
float real_array3[M];
float *preal1, *preal2, *preal3;
int32_t int_array1[M];
int32_t int_array2[M];
int32_t int_array3[M];
int32_t *pint1, *pint2, *pint3;


int32_t float2Qmpn(float realnum, uint32_t n) {
    int32_t temp = (int32_t)(realnum * (1<<n));
    if (temp) {
        return temp;
    } else {
        return 1; // the minimum nonzero number to avoid exception for DIV
    }
}

float Qmpn2float(int32_t intnum, uint32_t n) {
    return (float)intnum / (1<<n);
}


int main(void) {
    int i;
// Initialize the Qm.n data
    pint1 = int_array1,     pint2 = int_array2;
    preal1 = real_array1,   preal2 = real_array2;
    for (i = 0; i < M; i++) {
        *pint1++ = float2Qmpn(*preal1++, n); 
        *pint2++ = float2Qmpn(*preal2++, n); 
    }

// Task 1: for loop for C and asm summation
    preal1 = real_array1;  preal2 = real_array2;  preal3 = real_array3;
    printf("C Task 1: ");
    for (i = 0; i < M; i++) {
        *preal3 = *preal1++ + *preal2++; 
        printf("%4.2f ", *preal3++); 
    }
    printf("\n");

    pint1 = int_array1;    pint2 = int_array2;    pint3 = int_array3;
    aTask1(pint1, pint2, pint3, M);
    printf("A Task 1: ");
    for (i = 0; i < M; i++) {
        printf("%4.2f ", Qmpn2float(*pint3++, n)); 
    }
    printf("\n");
    
// Task 2: while loop for C and asm multiplication
    preal1 = real_array1;  preal2 = real_array2;  preal3 = real_array3;
    printf("C Task 2: ");
    i = 0;
    while (i < M) {
        *preal3 = *preal1++ * *preal2++; 
        printf("%4.2f ", *preal3++); 
        i++;
    }
    printf("\n");

    pint1 = int_array1;    pint2 = int_array2;    pint3 = int_array3;
    uint32_t M_n = M | (n << 16);   // Passing two parameters together
    aTask2(pint1, pint2, pint3, M_n);
    printf("A Task 2: ");
    for (i = 0; i < M; i++) {
        printf("%4.2f ", Qmpn2float(*pint3++, n)); 
    }
    printf("\n");
    
    // Task 3: do-while loop for C and asm division
    preal1 = real_array1;  preal2 = real_array2;  preal3 = real_array3;
    printf("C Task 3: ");
    i = M;
    do {
        *preal3 = *preal1++ / *preal2++; 
        printf("%4.2f ", *preal3++); 
        i--;
    } while (i);
    printf("\n");

    pint1 = int_array1;    pint2 = int_array2;    pint3 = int_array3;
    M_n = M | (n << 16);   // Passing two parameters together
    aTask3(pint1, pint2, pint3, M_n);
    printf("A Task 3: ");
    for (i = 0; i < M; i++) {
        printf("%4.2f ", Qmpn2float(*pint3++, n)); 
    }
    printf("\n");

    // Task 4: do-while loop for C and asm modulo operation
    pint1 = int_array1;    pint2 = int_array2;    pint3 = int_array3;
    printf("C Task 4: ");
    i = M;
    do {
        *pint3 = fmod(*pint1++, *pint2++); 
        printf("%4.2f ", Qmpn2float(*pint3, n)); 
        i--;
    } while (i);
    printf("\n");

    pint1 = int_array1;    pint2 = int_array2;    pint3 = int_array3;
    M_n = M | (n << 16);   // Passing two parameters together
    aTask4(pint1, pint2, pint3, M_n);
    printf("A Task 4: ");
    for (i = 0; i < M; i++) {
        printf("%4.2f ", Qmpn2float(*pint3++, n)); 
    }
    printf("\n");

    while (1);
}
