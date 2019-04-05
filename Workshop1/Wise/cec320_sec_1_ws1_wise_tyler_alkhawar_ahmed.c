#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

char str_c[30], str_v[30];

void uint16_2_binary_str(uint16_t num, char *cPtr);
void print_str_c(uint16_t num, char *cPtr);
void print_str_v(uint16_t num, char *cPtr_c, char *cPtr_v);


int main(void) {
    uint16_t test_num[] = {0x1234, 0x5678, 0x9ABC, 0xDEF0};
    int N = sizeof(test_num) / sizeof(test_num[0]);

    printf("Group Members: Tyler Wise & Ahmed Alkhawar\n");
    printf("Testing the printout of binary numbers:\n");
    for (int i = 0; i < N; i++) {
        //uint16_2_binary_str(test_num[i], str_c);
        printf("Compact display for 0x%X is ", test_num[i]);
        print_str_c(test_num[i], str_c);
        printf("\n");
        printf("Verbose display for 0x%X is ", test_num[i]);
        print_str_v(test_num[i], str_c, str_v);
        printf("\n");
    }

    while (1);
}

void uint16_2_binary_str(uint16_t num, char *cPtr) {
  for(int i = 0; i < 30; i++) {
    	*(cPtr + i) = 0;
  }
  for(int i = 0; i < 16 ; i++) {
    	*(cPtr++) = num & (1 << 15 - i) == 0 ? '0' : '1';
  }
  *(cPtr++) = '\0';
}

void print_str_c(uint16_t num, char *cPtr) {
  uint16_2_binary_str(num, cPtr);
  printf("%s", cPtr);
}

void print_str_v(uint16_t num, char *cPtr_c, char *cPtr_v) {
  char *cPtr_v_original = cPtr_v;
  
  uint16_2_binary_str(num, cPtr_c);

  *(cPtr_v++) = '0';
  *(cPtr_v++) = 'b';
   
  for(int i = 0; i < 17; i++) {
  	*(cPtr_v ++) = *(cPtr_c++);
  	if((i + 1) % 4 == 0 && i != 15) {
		*((++cPtr_v)) = '_';
	}
  }
  printf("%s\0", cPtr_v_original);
}
