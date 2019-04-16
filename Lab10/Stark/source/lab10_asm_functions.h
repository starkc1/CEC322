#ifndef __LAB10_ASM_FUNCTIONS_H
#define __LAB10_ASM_FUNCTIONS_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

// Count the number of binary 1's using Algorithm 1
uint32_t asm_number_of_1s_alg1(uint32_t x);

// Count the number of binary 1's using Algorithm 2
uint32_t asm_number_of_1s_alg2(uint32_t x);

// Count the number of binary 1's using Algorithm 3
uint32_t asm_number_of_1s_alg3(uint32_t x);

// Call Algorithm 2 in assembly
void asm_number_of_1s_alg2_asm_caller( 
            uint32_t *pIn,      // pointer to input uint32_t array
            uint32_t *PLen,     // pointer to output, the number of 1's, array
            uint32_t n);        // the number of elements in the input array

// Call Algorithm 3 in assembly
void asm_number_of_1s_alg3_asm_caller( 
            uint32_t *pIn,      // pointer to input uint32_t array
            uint32_t *PLen,     // pointer to output, the number of 1's, array
            uint32_t n);        // the number of elements in the input array

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LAB10_ASM_FUNCTIONS_H */
