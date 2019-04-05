#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern uint32_t aTask1(int32_t *arr, uint32_t n);
extern uint32_t aTask2(uint32_t n);
extern uint32_t aTask3(uint32_t n);
extern uint32_t aTask4(uint32_t n, uint32_t b);

// Global variable
int32_t array_e[8] = {-1, 5, 3, -8, 10, 23, 6, 5};
uint32_t rslt1, rslt2, rslt3, rslt4;
uint32_t num = 0xAAAAAAAA;

// For loop: Find the index of the min number in an array arr of size n
uint32_t cTask1(int32_t *arr, int32_t n) {
    uint32_t minLoc = 0;
		int32_t minValue = arr[0];
		for(int i = 0; i < n; i++) {
			if( *(arr + i) < minValue) {
				minLoc = i;
				minValue = *(arr + i);
			}
		}
    return minLoc;
}

// While loop: Determine the number of binary 1's using the parity-checking alg
uint32_t cTask2(uint32_t num) {
    uint32_t y, z;
    uint32_t count = num >> 31;
    while(num) {
        y =num<< 2;
        z = y >> 31;
        if(num << 1 > y) {
          count += z + 1;
        }
        else {
          count += z;
        }
       num= y;
    }
    return count;
}

// Do-while loop: Count the number of binary 1's using a simplified approach
uint32_t cTask3(uint32_t num) {
    uint32_t count = 0;
    int i = 0;
		do {
      count += (num >> i) & 0x1;
      i++;
    }
		while(i < 32);
    return count;
}

// Any loop: Count the number of digits (in terms of base b) of a number
uint32_t cTask4(uint32_t num, uint32_t b) {
    uint32_t count = 1;
    uint32_t maxVal = b;
    while(maxVal < num)
    {
      maxVal *= b;
      count++;
    }
    return count;
}


int main(void) {
    rslt1 = cTask1(array_e, 8);
    printf("C version of Task 1: rslt1 = %d \n", rslt1);
    rslt1 = 0;
    rslt1 = aTask1(array_e, 8);
    printf("ASM version of Task 1: rslt1 = %d \n", rslt1);

    rslt2 = cTask2(num);
    printf("C version of Task 2: rslt2 = %d \n", rslt2);
    rslt2 = 0;
    rslt2 = aTask2(num);
    printf("ASM version of Task 2: rslt2 = %d \n", rslt2);

    rslt3 = cTask3(num);
    printf("C version of Task 3: rslt3 = %d \n", rslt3);
    rslt3 = 0;
    rslt3 = aTask3(num);
    printf("ASM version of Task 3: rslt3 = %d \n", rslt3);

    num = 0123456;
    rslt4 = cTask4(num, 8);
    printf("C version of Task 4: rslt4 = %d \n", rslt4);
    rslt4 = 0;
    rslt4 = aTask4(num, 8);
    printf("ASM version of Task 4: rslt4 = %d \n", rslt4);

    while (1);
}
