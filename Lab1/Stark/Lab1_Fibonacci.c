//Lab 1 CEC 322 on 1/23/19

//Cameron Stark

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
//#include <string.h>
uint32_t eucl_norm; //stores euclidan norm
uint32_t fibo_array1[8]; //stores finbonacci values
uint32_t max_unit32_t; //stores max value



void func1_fibo(uint32_t *fibo_array, uint32_t N) {
		
		*(fibo_array + 0) = 1;
		*(fibo_array + 1) = 1;
		for (int i = 2; i < N; i++) {
			*(fibo_array + i) = *(fibo_array + (i-1)) + *(fibo_array + (i-2));
		}
}

int32_t func2_norm(uint32_t *fibo_array, uint32_t N) {
    float norm = 0.0;

    for (int i = 0; i < N; i++) {
         norm += *(fibo_array+i)**(fibo_array+i);
    }

    norm = sqrt(norm);
    return (int32_t)norm;
}

void func3_print(uint32_t *array, uint32_t N) {
	  printf("The first %d numbers of the array are:\n", N);
    for(int i = 0; i < N-1; i++) {
        printf("%d,  ", *(array + i));
    }
    printf("%d.\n", *(array + N-1));
    return;
}

int main(void) {

    char my_team[] = "Cameron Stark & Jacob Gattuso";
		printf("Results of Lab1 from %s.\n", my_team);
	
    printf("fibo_array address: 0x%p\n", fibo_array1);
    printf("eucl_norm address: 0x%p\n", &eucl_norm);
	
    max_unit32_t = 0xFFFFFFFF;
    printf("The address/value of max_uint32_t are respectively 0x%p and %u.\n", &max_unit32_t, max_unit32_t);
    
    func1_fibo(fibo_array1, 8);
    eucl_norm = func2_norm(fibo_array1, 8);
    func3_print(fibo_array1, 10);
	  while(1);
}
