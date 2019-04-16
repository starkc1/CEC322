	AREA asm_code, CODE, READONLY  
	
	EXPORT aTask1
	EXPORT aTask2
	EXPORT aTask3
	EXPORT aTask4
		
	ALIGN                           


; For loop: Find the index of the min number in an array arr of size n
; uint32_t aTask1(int32_t *arr, int32_t n); 
aTask1 PROC
	PUSH {r4, r5, lr}
	LDR r4, [r0] ; minVal
	MOV r3, #0 ; minLoc
	MOV r2, #0 ;i
aTask1_loop
	CMP r2, r1
	BGE aTask1_end
	LDR r5, [r0, r2, LSL #2]
	CMP r5, r4
	MOVLT r4, r5
	MOVLT r3, r2
	ADD r2, #1
	B aTask1_loop
aTask1_end
	MOV r0, r3
	POP {r4, r5, pc}
	BX lr
	ENDP

; While loop: Determine the number of binary 1's using the parity-checking alg
; uint32_t aTask4(uint32_t num); 
aTask2 PROC
	MOV r1, #0
	MOV r2, #0
aTask2_loop
	CBZ r0, aTask2_end	
	SUB r2, r0, #1 
	AND r0, r2, r0
	ADD r1, #1
	B aTask2_loop
aTask2_end
	MOV r0, r1
	BX lr
	ENDP

; Do-while loop: Count the number of binary 1's using a simplified approach
; uint32_t aTask3(uint32_t x);
aTask3 PROC 
	MOV r1, r0, LSR #31
aTask3_loop
	MOVS r0, r0, LSL #2
	ADC r1, r0, LSR #31
	CBZ r0, aTask3_end
	B aTask3_loop
aTask3_end
	MOV r0, r1
	BX LR
	ENDP

; Count the number of deimal digits of an uint32_t number
; uint32_t aTask4(uint32_t n, uint32_t b);
aTask4 PROC
	MOV r1, #0
	MOV r2, #8
aTask4_loop
	CBZ r0, aTask4_end
	UDIV r0, r0, r2
	ADD r1, #1
	B aTask4_loop
aTask4_end
	MOV r0, r1
	BX lr
	ENDP
	
	
	END     
	