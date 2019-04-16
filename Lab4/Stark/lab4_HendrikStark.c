#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

void uint8_2_binary_str(uint8_t num, char *cPtr);
void int8_2_binary_str(int8_t num, char *cPtr);
void print_str_v(uint8_t num, char *cPtr_c, char *cPtr_v);
uint8_t sub_uint8(uint8_t x0, uint8_t x1, bool *c_flg);  // return x0 - x1
int8_t sub_int8(int8_t x0, int8_t x1, bool *v_flg);      // return x0 - x1
int count;

#define P 8 // the number of pairs of data to be operated on
#define N 8 // number of bits
#define MIN_UN 0    // minimum value of unsigned N-bit number
#define MAX_UN ((1 << N) - 1)   // maximum value of unsigned N-bit number
#define MIN_IN (-(1 << (N-1)) ) // minimum value of signed N-bit number
#define MAX_IN ((1 << (N-1)) - 1)   // maximum value of signed N-bit number

char str_c[30], str_v[30];
int8_t x[P][2];
uint8_t ru[P];
int8_t ri[P];
bool c[P], v[P]; 

int main(void) {
    for (int i = 0; i < P; i++) {
        x[i][0] = rand() % MAX_UN + MIN_IN;
        x[i][1] = rand() % MAX_UN + MIN_IN;
        printf("x[%d] = %d, %d \n", i, x[i][0], x[i][1]);
        
        ru[i] = sub_uint8(x[i][0], x[i][1], &c[i]);
        printf("result_u = %d, C flag = %d\n", ru[i], c[i]);
				uint8_2_binary_str(ru[i], str_c);
        print_str_v(ru[i], str_c, str_v), printf("\n\n");
        
        ri[i] = sub_int8(x[i][0], x[i][1], &v[i]);
        printf("result_i = %d, V flag = %d\n", ri[i], v[i]);  
				int8_2_binary_str(ri[i], str_c);
        print_str_v(ri[i], str_c, str_v), printf("\n\n");
        
        int temp0 = (x[i][0] << (32-N));
        int temp1 = (x[i][1] << (32-N));
        int temp2 = temp0 - temp1;
        int temp = temp2 >> (32-N);
        printf("result_arm = %d\n\n\n", temp);
    }	
    
    while (1);
}




void uint8_2_binary_str(uint8_t num, char *cPtr)
{
    count = 0;

    for (int cow = 7; cow >= 0; cow--)
    {
        int k = num >> cow;
        
        if (k & 1) {
            *(cPtr + count) = '1';
        } else {
            *(cPtr + count) = '0';
        }
        count++;
    }
}

void int8_2_binary_str(int8_t num, char *cPtr)
{
    count = 0;
	
		if(num < 0){
			num *= -1;
			num = ~num;
			num++;
		}

    for (int cow = 7; cow >= 0; cow--)
    {
        int k = num >> cow;
        
        if (k & 1) {
            *(cPtr + count) = '1';
        } else {
            *(cPtr + count) = '0';
        }
        count++;
    }
}

void print_str_v(uint8_t num, char *cPtr_c, char *cPtr_v)
{
    for (int i = 0, j = 0, k = 0; i < 9; i++) {
        if (j == 4)  {
            *(cPtr_v + i) = '_';
            j = 0;
        } else if (j != 4) {
            *(cPtr_v + i) = *(cPtr_c + k);
            k++;
            j++;
        }
    }

    printf("0b%s", cPtr_v);
}


uint8_t  sub_uint8(uint8_t x0, uint8_t x1, bool *c_flg) {
	
		uint8_t result = x0 - x1;	
	
		if(result > x0){
			*c_flg = 0;//1
		} else {
			*c_flg = 1;//0
		}
		
		printf("%u - %u = %u\n", x0, x1, result);
		//printf("The result is %u, and the C = %d\n", result, *c_flg);
		return result;
}
        
int8_t  sub_int8(int8_t x0, int8_t x1, bool *v_flg) {
	
	int8_t result = x0 - x1;
	
	if(x0 < 0 && x1 > 0 && result > 0){
		*v_flg = 1;
	} else if(x0 > 0 && x1 < 0 && result < 0) {
		*v_flg = 1;
	} else {
		*v_flg = 0;
	}
		
		
		printf("%i - %i = %i\n", x0, x1, result);

		//printf("The result is %i, and the V = %d\n", result, *v_flg);
		
		return result;
}