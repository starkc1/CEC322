                AREA my_fancy_asm_code, CODE, READONLY

                EXPORT aTask1
                EXPORT aTask2
                EXPORT aTask3
                EXPORT aTask4

                ALIGN


; For loop: Find the index of the min number in an array arr of size n
; uint32_t aTask1(int32_t *arr, int32_t n);
aTask1          PROC
                PUSH    {r4, r5, lr}
				;uint32_t minLoc = 0;
				;int32_t minValue = arr[0];
				;for(int i = 0; i < n; i++) {
				;	if( *(arr + i) < minValue) {
				;		minLoc = i;
				;		minValue = *(arr + i);
				;	}
				;}
				;
				MOV r2, #0			;minLocation
				LDR r3, [r0], #4	;minValue
				MOV r4, #1			;i
aTask1_loop
				CMP r1, r4
				BLT aTask1_endLoop
				LDR r5, [r0], #4
				CMP r5, r3
				BGE aTask1_endIf
				MOV r2, r4
				MOV r3, r5
aTask1_endIf
				ADD r4, #1
				B aTask1_loop
aTask1_endLoop
				MOV r0, r2
                POP     {r4, r5, pc}
                ENDP

; While loop: Determine the number of binary 1's using the parity-checking alg
; uint32_t aTask4(uint32_t num);
aTask2          PROC
                MOV r1, r0, LSR #31
aTask2_loop     CBZ r0, aTask2_end
                MOVS r0, r0, LSL #2
                ADC r1, r0, LSR #31
                B aTask2_loop
aTask2_end      MOV r0, r1
                BX      LR
                ENDP

; Do-while loop: Count the number of binary 1's using a simplified approach
; uint32_t aTask3(uint32_t x);
aTask3          PROC
				;do {
        ;  count += (num >> i) & 0x1;
        ;  i++
        ;}
    		;while(i < 32);
				MOV r1, #0
				MOV r2, #0
task3_loop		CMP r2, #32
				BGE task3_endLoop

				LSLS r0, #1
				ADC r1, #0


				ADD r2, #1
				B task3_loop
task3_endLoop
				MOV r0, r1
                BX      LR
                ENDP

; Count the number of deimal digits of an uint32_t number
; uint32_t aTask4(uint32_t n, uint32_t b);
aTask4      PROC

            MOV r2, #1;
            MOV r3, r1;
task4_loop  CMP r0, r3
            BLT task4_end
            MUL r3, r1;
            ADD r2, #1;
            B   task4_loop
task4_end
            MOV r0, r2
            BX  lr
            ENDP


            END
