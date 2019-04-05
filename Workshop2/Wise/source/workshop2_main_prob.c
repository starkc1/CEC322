#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Prototype of FOUR functions, each for a STATE.
// The func in State 1 performs addition of "unsigned numbers" x0 and x1.
int s1_add_uintN(int x0, int x1, bool *c_flg);
// The func in State 2 performs addition of "signed numbers" x0 and x1.
int s2_add_intN(int x0, int x1, bool *v_flg);
// The func in State 3 performs subtraction of "unsigned numbers" x0 and x1.
int s3_sub_uintN(int x0, int x1, bool *c_flg);
// The func in State 3 performs subtraction of "signed numbers" x0 and x1.
int s4_sub_intN(int x0, int x1, bool *v_flg);

// We define the number of bits and the related limits of unsigned and 
// and signed numbers.
#define N 5         // number of bits
#define MIN_U 0     // minimum value of unsigned N-bit number
#define MAX_U ((1 << N) - 1)   // maximum value of unsigned N-bit number
#define MIN_I (-(1 << (N-1)) ) // minimum value of signed N-bit number
#define MAX_I ((1 << (N-1)) - 1)   // maximum value of signed N-bit number
 
// We use the following three pointers to access data, which can be changed
// when the program pauses. We need to make sure to have the RAM set up
// for these addresses. 
int *pIn = (int *)0x20010000U;   // the value of In should be -1, 0, or 1.
int *pX0 = (int *)0x20010004U;   // X0 and X1 should be N-bit integers.
int *pX1 = (int *)0x20010008U;
    
int main(void) {
	printf("Team Members: Tyler Wise\n\n");
	
    enum progState{State1 = 1, State2, State3, State4};
    enum progState cState = State1;         // Current State
    bool dataReady = false;
    bool cFlg, vFlg;
    int result;
    
    while (1) {
        dataReady = false;
        // Check if the data are legitimate
        while (!dataReady) {
            printf("Halt program here to provide correct update of data\n");
            printf("In should be -1, 0, and 1 and ");
            printf("X0 and X1 should be N-bit SIGNED integers\n");
            if (((-1 <= *pIn) && (*pIn <= 1)) && 
                    ((MIN_I <= *pX0) && (*pX0 <= MAX_I)) &&
                    ((MIN_I <= *pX1) && (*pX1 <= MAX_I))) {
                dataReady = true;
            }
        }
        printf("Your input: In = %d, X0 = %d, X1 = %d \n", *pIn, *pX0, *pX1);
        
        switch (cState) {
          case State1: 
            result = s1_add_uintN(*pX0, *pX1, &cFlg);
            printf("State = %d, rslt = %d, Cflg = %d\n", cState, result, cFlg);
            cState += *pIn;
            if (cState < State1) cState += State4;
            break;
          case State2: 
            result = s2_add_intN(*pX0, *pX1, &vFlg);
            printf("State = %d, rslt = %d, Vflg = %d\n", cState, result, vFlg);
            cState += *pIn;
            break;
          case State3: 
						result = s3_sub_uintN(*pX0, *pX1, &cFlg);
            printf("State = %d, rslt = %d, Cflg = %d\n", cState, result, cFlg);
            cState += *pIn;
            break;
          case State4: 
						result = s4_sub_intN(*pX0, *pX1, &vFlg);
            printf("State = %d, rslt = %d, Vflg = %d\n", cState, result, vFlg);
            cState += *pIn;
						if (cState > State4) cState = State1;
            break;
          default:
            printf("Error with the program state\n");
        }
    }
}

int  s1_add_uintN(int x0, int x1, bool *c_flg) {
    if (x0 < 0) x0 = x0 + MAX_U + 1;
    if (x1 < 0) x1 = x1 + MAX_U + 1;
    int temp = x0 + x1;
    if (temp > MAX_U) {
        temp = temp - (MAX_U + 1);
        *c_flg = true;
    } else {
        *c_flg = false;
    }
    return temp;
}
        
int  s2_add_intN(int x0, int x1, bool *v_flg) {
    int temp = x0 + x1;
    if (temp < MIN_I) {
        temp = temp + MAX_U + 1;
        *v_flg = true;
    } else if (temp > MAX_I) {
        temp = temp - (MAX_U + 1);
        *v_flg = true;
    } else {
        *v_flg = false;
    }
    return temp;
}

int  s3_sub_uintN(int x0, int x1, bool *c_flg) {
    int temp = x0 - x1;
		if(temp < 0){
			temp += MAX_U + 1;
		}
    if (temp > x0) {
        *c_flg = 0;
    } else {
        *c_flg = 1;
    }
    return temp;
}
        
int  s4_sub_intN(int x0, int x1, bool *v_flg) {
  int temp = x0 - x1;

	if(x1 > 0 && x0 < 0 && temp > 0){
		*v_flg = 1;
	}else if(x1 < 0 && x0 > 0 && temp < 0){
		*v_flg = 1;
	}else {
		*v_flg = 0;
	}
	
  return temp;
}
