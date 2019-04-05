#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
void uint8_2_binary_str(uint8_t num, char *cPtr);
void print_str_v(uint8_t num, char *cPtr_c, char *cPtr_v);
uint8_t sub_uint8(uint8_t x1, uint8_t x2, bool *cFlg);
int8_t sub_int8(int8_t x1, int8_t x2, bool *vFlg);
#define P 8
#define N 8
#define MIN_UN 0
#define MAX_UN ((1 << N) - 1)
#define MIN_IN (-(1 << (N-1)))
#define MAX_IN ((1 << (N-1)) -1)
char str_c[30], str_v[30];
int8_t x[P][2];
uint8_t ru[P];
int8_t ri[P];
bool c[P], v[P];

int main(void) {
    printf("Group Members: Tyler Wise & Andrew Henderson\n");
    for (int i = 0; i < P; i++) {
			x[i][0] = rand() % MAX_UN + MIN_IN;
			x[i][1] = rand() % MAX_UN + MIN_IN;
			printf("x[%d] = %d, %d \n", i, x[i][0], x[i][1]);
			
			ru[i] = sub_uint8(x[i][0], x[i][1], &c[i]);
			printf("result_u = %d, C flag = %d \n", ru[i], c[i]);
		  print_str_v(ru[i], str_c, str_v);
      printf("\n");
    	
			ri[i] = sub_int8(x[i][0], x[i][1], &v[i]);
			printf("result_i = %d, V flag = %d \n", ri[i], v[i]);
		  print_str_v(ri[i], str_c, str_v);
      printf("\n");
			
			int temp0 = (x[i][0] << (32-N));
			int temp1 = (x[i][1] << (32-N));
			int temp2 = temp0 - temp1;
			int temp = temp2 >> (32-N);
			printf("ARM result = %d\n", temp);
    }
    while (1);
}

void uint8_2_binary_str(uint8_t num, char *cPtr) {
  for(int i = 0; i < 30; i++) {
    	*(cPtr + i) = 0;
  }
  for(int i = 0; i < 8 ; i++) {
    	*(cPtr++) = (num & (1 << (7 - i))) == 0 ? '0' : '1';
	}
  *(cPtr++) = '\0';
}

void print_str_v(uint8_t num, char *cPtr_c, char *cPtr_v) {
  char *cPtr_v_original = cPtr_v;
  uint8_2_binary_str(num, cPtr_c);
  printf("0b");
  for(int i = 0; i < 8; i++) {
  	printf("%c", *(cPtr_c++));
		if((i + 1) % 4 == 0 && i != 7) {
			printf("_");
		}
  }
}


uint8_t sub_uint8(uint8_t x0, uint8_t x1, bool *cFlg){
		uint8_t temp = x0 - x1;
		if(temp < 0)
		{
			temp += MAX_UN;
		}else if(temp > MAX_UN)
		{
			temp -= MAX_UN;
		}
    if (temp > x0) {
        *cFlg = 0;
    } else {
        *cFlg = 1;
    }
    return temp;
}


int8_t sub_int8(int8_t x0, int8_t x1, bool *vFlg) {
	int8_t temp = x0 - x1;
  
	if(temp < MIN_IN)
	{
		temp += MAX_IN;
	}
	else if(temp > MAX_IN)
	{
		temp -= MAX_IN;
	}
	
	if(x1 > 0 && x0 < 0 && temp > 0){
		*vFlg = 1;
	}else if(x1 < 0 && x0 > 0 && temp < 0){
		*vFlg = 1;
	}else {
		*vFlg = 0;
	}
	
  return temp;
}
