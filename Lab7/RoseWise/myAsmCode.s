        AREA my_fancy_asm_code, CODE, READONLY   ; Define the program area

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
			
        ALIGN                   ; Align the data in the boundary of 4 bytes.

;uint32_t task1(uint32_t a, uint32_t x);
task1  	PROC

		CMP r1, r0
		BGE	end_if1
		LSR r0, #2
		ADD r0, #1
end_if1
		BX lr
		ENDP
;uint32_t task2(uint32_t a, uint32_t x);
task2  	PROC

		CMP r1, #20
		BLE else_succ3
		CMP r1, #25
		BLT end_if2
else_succ3
		LSL r0, #1
		SUB r0, #1
end_if2
		BX lr
		ENDP
;uint32_t task3(uint32_t a, uint32_t x);
task3  	PROC
		MOV r3, r1, LSL #3
		CMP r0, r3
		BNE	else_3
		SUBS r1, #10
		B end_if3
else_3
		SUBS r1, #4
		B end_if3
end_if3
    MOV r0, r1
		BX lr
		ENDP

;uint32_t task4(uint32_t a, uint32_t x);
task4   PROC

		CMP r1, #20
		BGE else_succ4
		CMP r1, #25
		BGT else4
else_succ4
		ADD r0, #1
		LSL r0, #3
		B end_if4
else4

		SUB r0, #1
		LSL r0, #4

end_if4
		BX lr
		ENDP
;uint32_t task5(uint32_t n);
task5  	PROC
        MOV  r1, #0             ; variable (int) i
        MOV r2, #0              ; sum5 = 0
task5_loop
        CMP  r1, r0
        BGE  task5_end
        ADD  r3, r1, #2
        LSL r3, #3
        ADD r2, r3
        ADD r1, #1
        B    task5_loop            ; branch to task5_loop
task5_end
        MOV r0, r2
        BX   lr                     ; return
        ENDP

;uint32_t task6(uint32_t *ptr, uint32_t n);
task6   PROC
		PUSH{r4 -r6, lr}
        MOV r3, #0; sum
        MOV r4, #0; i
for_loop6
        CMP r1, r4
        BLE end_loop6
		
		LDR r6, [r0], #4
		AND r6, #0x0F
		ADD r3, r6
		
		ADD r4, #1
		B for_loop6
end_loop6
		MOV r0, r3
		POP {r4-r6, pc}
		ENDP

;uint32_t task7(uint32_t n);
task7   PROC
        MOV r1, #0
        MOV r2, #0
task7_loop
        CMP r1, r0
        BGE task7_end
        MOV r3, r1, LSL #2
        ORR r3, #15
        ADD r2, r3
        ADD r1, #1
        B task7_loop
task7_end
        MOV r0, r2
		BX lr
		ENDP

;uint32_t task8(uint32_t *ptr, uint32_t n);
task8   PROC
        MOV r2, #0; sum
loop_8
		CMP r1, #0
		BLE endloop_8
		
		SUB r1, #1
		LDR r3, [r0, r1, LSL #2]
		ADDS r2, r3
		
		B loop_8
endloop_8
		MOV r0, r2
		BX lr
		ENDP

;uint32_t task9(uint32_t n);
task9   PROC
        MOV r1, #0
        MOV r2, #0
task9_loop
        MOV r3, r1, LSL #2
        ORR r3, #15
        ADD r2, r3
        ADD r1, #1
        CMP r1, r0
        BLT task9_loop
task9_end
        MOV r0, r2
		BX lr
        ENDP

;uint32_t task10(uint32_t *ptr, uint32_t n);
task10  PROC
		PUSH{r4-r5, lr}
		MOV r3, #0
task10_loop
		CMP r1, #0
		BLE task10_end
		
		LDR r4, [r0], #4
		LSL r4, #1
		ADD r3, r4
		SUB r1, #1
		

		B task10_loop
task10_end
		MOV r0, r3
		POP{r4-r5, pc}
		ENDP
			
			
        END
