#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lab10_c_functions.h"
#include "lab10_asm_functions.h"

#define NUM_ELE  10
uint32_t A = 0, B = 0xAAAAAAAA, C = 0xFFFFFFFF;
uint32_t array_data[NUM_ELE], array_nof1a[NUM_ELE], array_nof1b[NUM_ELE];
uint32_t array_nof1c[NUM_ELE], array_nof1d[NUM_ELE];
uint32_t breakPointHere = 0;       // Used only for creating breakpoints

int main(void) {
    uint32_t myID = 1234;   // The last 4 digit of your ERAU ID
    srand(myID);            // Seed the random number generator
    for (int i = 0; i < NUM_ELE; i++) {
        array_data[i] = 2*rand();
    }

    uint32_t num_of_1a, num_of_1b, num_of_1c;

// Evaluate C functions
    num_of_1a = C_number_of_1s_alg1(A);
    num_of_1b = C_number_of_1s_alg1(B);
    num_of_1c = C_number_of_1s_alg1(C);
    printf("C Alg 1: A: %d, B: %d, C: %d\n", num_of_1a, num_of_1b, num_of_1c);

    num_of_1a = 0, num_of_1b = 0, num_of_1c = 0;
    num_of_1a = C_number_of_1s_alg2(A);
    num_of_1b = C_number_of_1s_alg2(B);
    num_of_1c = C_number_of_1s_alg2(C);
    printf("C Alg 2: A: %d, B: %d, C: %d\n", num_of_1a, num_of_1b, num_of_1c);

    num_of_1a = 0, num_of_1b = 0, num_of_1c = 0;
    num_of_1a = C_number_of_1s_alg3(A);
    num_of_1b = C_number_of_1s_alg3(B);
    num_of_1c = C_number_of_1s_alg3(C);
    printf("C Alg 3: A: %d, B: %d, C: %d\n", num_of_1a, num_of_1b, num_of_1c);

// Evaluate asm functions
    num_of_1a = 0, num_of_1b = 0, num_of_1c = 0;
    num_of_1a = asm_number_of_1s_alg1(A);
    num_of_1b = asm_number_of_1s_alg1(B);
    num_of_1c = asm_number_of_1s_alg1(C);
    printf("Asm Alg 1: A: %d, B: %d, C: %d\n", num_of_1a, num_of_1b, num_of_1c);

    num_of_1a = 0, num_of_1b = 0, num_of_1c = 0;
    num_of_1a = asm_number_of_1s_alg2(A);
    num_of_1b = asm_number_of_1s_alg2(B);
    num_of_1c = asm_number_of_1s_alg2(C);
    printf("Asm Alg 2: A: %d, B: %d, C: %d\n", num_of_1a, num_of_1b, num_of_1c);

    num_of_1a = 0, num_of_1b = 0, num_of_1c = 0;
    num_of_1a = asm_number_of_1s_alg3(A);
    num_of_1b = asm_number_of_1s_alg3(B);
    num_of_1c = asm_number_of_1s_alg3(C);
    printf("Asm Alg 3: A: %d, B: %d, C: %d\n", num_of_1a, num_of_1b, num_of_1c);


// Use C functions in loops to process an array of data
    breakPointHere++;
    for (int i = 0; i < NUM_ELE; i++) {
        array_nof1a[i] = C_number_of_1s_alg1(array_data[i]);
    }


/* C program assignment A: Repeat the above block of code using pointers. 
   * Call C_number_of_1s_alg2 in the loop.
   * Use pointers to array_data and array_nof1b in the postfix format. 
      * For examples of this usage, see the C code of Lab 06.
      * You may have to define and initialize your pointers.
 */
    breakPointHere++;
		uint32_t *pointerArray = array_data;
    for (int i = 0; i < NUM_ELE; i++) {
        array_nof1a[i] = C_number_of_1s_alg2(*(pointerArray++));
    }


/* C program assignment B: Repeat the above block of code using pointers again. 
   * Call C_number_of_1s_alg3 in the loop.
   * Use pointers to array_data and array_nof1c in the prefix format. 
       For examples of this usage, see the C code of Lab 06.
 */
    breakPointHere++; 
		uint32_t *pointerArray2 = array_data;
    for (int i = 0; i < NUM_ELE; i++) {
        array_nof1a[i] = C_number_of_1s_alg3(*(++pointerArray2));
    }


/* Asm program illustration: for details, see lab10_asm_function.s. 
   * Call the function using pointers to array_data, array_nof1d, and NUM_ELE.
   * USE POINTERS IN THE POSTFIX INCREMENT FORMAT.
 */
    breakPointHere++; 
    asm_number_of_1s_alg2_asm_caller(array_data, array_nof1d, NUM_ELE);

    breakPointHere++; 
    for (int i = 0; i < NUM_ELE; i++) {
        printf("Rand = %x; ", array_data[i]);
        printf("Nof1a = %d, Nof1b = %d, ", array_nof1a[i], array_nof1b[i]);
        printf("Nof1c = %d, Nof1d = %d\n", array_nof1c[i], array_nof1d[i]);
    }

    printf("\n");

/* Asm program assignment: for details, see lab10_asm_function.s. 
   * Call the function using pointers to array_data, array_nof1d, and NUM_ELE
   * USE POINTERS IN THE PREFIX INCREMENT FORMAT.
 */
    breakPointHere++; 
    asm_number_of_1s_alg3_asm_caller(array_data, array_nof1d, NUM_ELE);

    breakPointHere++; 
    for (int i = 0; i < NUM_ELE; i++) {
        printf("Rand = %x; ", array_data[i]);
        printf("Nof1a = %d, Nof1b = %d, ", array_nof1a[i], array_nof1b[i]);
        printf("Nof1c = %d, Nof1d = %d\n", array_nof1c[i], array_nof1d[i]);
    }


    while(1);
}
