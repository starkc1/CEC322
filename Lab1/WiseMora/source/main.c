//#include <stm32l476xx.h>  // Comment out this file while using simulator
#include <stdio.h>
#include <stdint.h>
#include <math.h>

uint32_t max_uint32_t;  
uint32_t eucl_norm;
uint32_t fibo_array[8];

void func1_fibo(uint32_t *fibo_array, uint32_t n) {
	for(uint32_t i = 0; i < n; i++) {
		if(i == 0 || i == 1){
			*(fibo_array) = 1;
		} else {
			*(fibo_array) = *(fibo_array - 1) + *(fibo_array - 2);
		}
		fibo_array++;
	}
}

int32_t func2_norm(uint32_t *fibo_array, uint32_t n) {
	float norm = 0.0f;
	for(uint32_t i =0; i < n; i++) {
		norm += *fibo_array * *fibo_array;
		fibo_array++;
	}
	norm = sqrtf(norm);
	return (int32_t) norm;
}

int32_t func3_print(uint32_t *fibo_array, uint32_t n) {
	for(uint32_t i = 0; i < n; i++) {
		printf("The fibonacci value for %d is %d.\n", i, *fibo_array);
		fibo_array++;
	}
}

int main(void) {
   char my_team[] = "Tyler Wise & Luis Mora";
    printf("Results of Lab 1 from %s.\n", my_team);
	
	printf("fibo_array is located at 0x%p\n", fibo_array);
	printf("eucl_norm is located at 0x%p\n", &eucl_norm);
	max_uint32_t = 0xFFFFFFFF;
	printf("max_uint32_t is at 0x%p and has the value %u.\n", &max_uint32_t, max_uint32_t);
	func1_fibo(fibo_array, 8);
	eucl_norm = func2_norm(fibo_array, 8);
	func3_print(fibo_array, 10);
    while (1);
}
