	AREA asm_code, CODE, READONLY   ; Define the program area

	; Export functions defined in this file. These functions need to be declared
	; in the file calling them.
	EXPORT task1
	EXPORT task2
	EXPORT task3
	EXPORT task4
	EXPORT task5
	EXPORT task6
	EXPORT task7
	EXPORT task8
	EXPORT task9
	EXPORT task10
	
	
	IMPORT input_array
	IMPORT output_array
		
	ALIGN                   ; Align the data in the boundary of 4 bytes.


task1	PROC
	CMP r0, r1
	BGT task1_true
task1_true 
	LSR r0, #2
	ADD r0, #1
task1_end
	BX lr
	ENDP



task2	PROC
	CMP r1, #20 
	BLE task2_true
	BGT task2_false
task2_false
	CMP r1, #25
	BGE task2_true
task2_true
	LSL r0, #1
	SUB r0, #1
task2_end
	BX lr
	ENDP
		
		
task3	PROC
	CMP r0, r1, LSL #3
	BEQ	task3_true
task3_false	
	SUB r1, #4
	B task3_end
task3_true
	SUB r1, #10
task3_end
	MOV r0, r1
	BX lr
	ENDP
		
		
task4	PROC
	CMP r1, #20
	BLE task4_true
	BGT task4_false
task4_false
	CMP r1, #25
	BGE task4_true
	BLT task4_else
task4_else
	SUB r0, #1
	LSL r0, #4
	B task4_end
task4_true
	ADD r0, #1
	LSL r0, #3
	B task4_end
task4_end
	BX lr
	ENDP
		


task5	PROC
	PUSH {r4,lr}
	MOV r2, #0	;sum
	MOV r3, #0	;i
	MOV r4, #0	;temp i
task5_loop
	CMP r3, r0
	BGE task5_end
	MOV r4, r3
	ADD r4, #2
	LSL r4, #3
	ADD r2, r4
	ADD r3, #1
	B task5_loop
task5_end
	MOV r0, r2
	POP {r4, pc}
	BX lr
	ENDP
		


task6	PROC
	PUSH {r4, lr}
	MOV r2, #0 ;sum6
	MOV r3, #0 ;i
task6_loop
	CMP r3, r1
	BGE task6_end
	LDR r4, [r0], #4
	AND r4, #0x0F
	ADD r2, r4
	ADD r3, #1
	B task6_loop
task6_end
	MOV r0, r2
	POP {r4, pc}
	BX lr
	ENDP
			
			
			
task7	PROC
	PUSH {r4, lr}
	MOV r2, #0 ;sum7
	MOV r3, #0 ;i
	MOV r4, #0 ;temp i
task7_while
	CMP r3, r0
	BGE task7_end
	MOV r4, r3
	LSL r4, #2
	ORR r4, #0x0F
	ADD r2, r4
	ADD r3, #1
	B task7_while
task7_end
	MOV r0, r2
	POP {r4, pc}
	BX lr
	ENDP
		


task8	PROC
	MOV r2, #0 ;sum8
	MOV r3, #0 ;temp
task8_while
	CMP r1, #0
	BLE task8_end
	SUB r1, #1
	LDR r3, [r0, r1, LSL #2]
	ADD r2, r3
	B task8_while
task8_end
	MOV r0, r2
	BX lr
	ENDP
			
			
			
task9	PROC
	PUSH {r4, lr}
	MOV r2, #0 ;sum9
	MOV r3, #0 ;i
	MOV r4, #0 ;temp i
task9_loop
	LSL r4, #2
	ORR r4, #0x0F
	ADD r2, r4
	ADD r3, #1
	MOV r4, r3
	CMP r3, r0
	BLT task9_loop
task9_end
	MOV r0, r2
	POP {r4, pc}
	BX lr
	ENDP
		


task10	PROC
	PUSH {r4, lr}
	MOV r2, #0 ;sum9
	MOV r3, #0 ;temp
	MOV r4, #0 ;temp
task10_loop
	CMP r1, #0
	BLE task10_end
	LDR r3, [r0], #4
	LSL r3, #1
	ADD r2, r3
	SUB r1, #1
	B task10_loop
task10_end
	MOV r0, r2
	POP {r4, pc}
	BX lr
	ENDP