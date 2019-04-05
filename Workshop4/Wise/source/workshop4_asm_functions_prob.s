                AREA my_fancy_asm_code, CODE, READONLY  

                EXPORT aTask1
                EXPORT aTask2
                EXPORT aTask3
                EXPORT aTask4
                    
                ALIGN                           


; extern void aTask1(int32_t *arr1, int32_t *arr2, int32_t *arr3, uint32_t M);
aTask1          PROC
                PUSH    {r4-r6, lr}
				MOV 	r4, #0
aTask1_loop	    CMP 	r4, r3
				BGE 	aTask1_end
				LDR 	r5, [r0], #4
				LDR 	r6, [r1], #4
				ADD		r5, r6
				STR 	r5, [r2], #4
				ADD 	r4, #1
				B		aTask1_loop
aTask1_end      POP     {r4-r6, pc}
                ENDP

; extern void aTask2(int32_t *arr1, int32_t *arr2, int32_t *arr3, uint32_t M_n);
; M_n = M | (n << 16)
aTask2          PROC
                PUSH    {r4-r7, lr}
				MOV 	r7, r3
				LSR 	r7, #16
				LSL		r3, #16
				LSR 	r3, #16
				MOV 	r4, #0
aTask2_loop	    CMP 	r4, r3
				BGE 	aTask2_end
				LDR 	r5, [r0], #4
				LDR 	r6, [r1], #4
				MUL		r5, r6
				ASR 	r5, r7
				STR 	r5, [r2], #4
				ADD 	r4, #1
				B		aTask2_loop
aTask2_end      POP     {r4-r7, pc}
                ENDP

; extern void aTask3(int32_t *arr1, int32_t *arr2, int32_t *arr3, uint32_t M_n);
; M_n = M & (n << 16)
aTask3          PROC
                PUSH    {r4-r7, lr}
 				MOV 	r7, r3
				LSR 	r7, #16
				LSL		r3, #16
				LSR 	r3, #16
				MOV 	r4, r3
aTask3_loop		LDR 	r5, [r0], #4
				LDR 	r6, [r1], #4
				LSL 	r5, r7
				SDIV	r5, r6
				STR 	r5, [r2], #4
				SUB 	r4, #1
				CMP 	r4, #0
				BGT 	aTask3_loop
aTask3_end      POP     {r4-r7, pc}
                ENDP

; extern void aTask3(int32_t *arr1, int32_t *arr2, int32_t *arr3, uint32_t M_n);
; M_n = M & (n << 16)
aTask4          PROC
                PUSH    {r4-r8, lr}
				MOV 	r7, r3
				LSR 	r7, #16
				LSL		r3, #16
				LSR 	r3, #16
				MOV 	r4, #0
aTask4_loop	    CMP 	r4, r3
				BGE 	aTask4_end
				LDR 	r5, [r0], #4
				LDR 	r6, [r1], #4
				SDIV 	r8, r5, r6
				MLS		r5, r6, r8, r5
				STR 	r5, [r2], #4
				ADD 	r4, #1
				B		aTask4_loop
aTask4_end      POP     {r4-r8, pc}
                ENDP



                END
                    