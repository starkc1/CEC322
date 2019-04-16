        AREA my_fancy_asm_code, CODE, READONLY   ; Define the program area

        ; Export functions defined in this file. These functions need to be declared
        ; in the file calling them.
        EXPORT task10
        EXPORT task11
        EXPORT task12
        EXPORT task13
        EXPORT task14
        EXPORT task15

        ALIGN                   ; Align the data in the boundary of 4 bytes.

task10  PROC
        MOV  r2, #0             ; variable (int) i
task10_loop
        CMP  r2, r1                 ; test = r2 - r1
        BGE  task10_end             ; if test >= 0, then branch to task10_end
        MOV  r3, r2, LSL #2         ; r3 <- r2 * 4
        SUB  r3, #15                ; r3 <- r3 - 15
        STRH r3, [r0, r2]           ; r3 -> mem[r0 + r2] or r3 -> mem[r0 + i]
        ADD  r2, #1                 ; r2 <- r2 + 1
        B    task10_loop            ; branch to task10_loop
task10_end
        BX   lr                     ; return
        ENDP

; If you need to use registers starting from r4, you need to PUSH them first to save the
; run-time environment for the caller. You need to POP them up at the exit of the code.

task11  PROC
		;setup registers
		MOV r2, #0
task11_loop
		CMP r2, r1
		BGE task11_end
		MOV r3, r2, LSL #5
		ADD r3, #2
		STRB r3, [r0, r2]
		ADD r2, #1
		B	task11_loop
task11_end
		BX lr
		ENDP

task12  PROC
        PUSH {r4-r5, lr}
        MOV  r3, #0
task12_loop
        CMP  r3, r2
        BGE  task12_end
        LDRSB  r2, [r0, r3]
        LDR  r5, =10
        SUB  r5, r4
        STRH r5, [r1, r3, LSL #1]
        ADD  r4, #1
        STRB r4, [r0, r3]
        ADD  r3, #1
        B    task12_loop
task12_end
        POP  {r4-r5, pc}       ; Pop lr to pc, which is the same as BX lr.
        ENDP

task13  PROC
		PUSH {r4-r6, lr}
        ;register setup
		;r0 = gVar - 1, r1 = i, r2 = &gPtrArray11a
		;while r1 > r0
		;task13(gPtrArray11a, gPtrArray13a, gVar1);
        SUB r2, #1
		MOV r6, #0
task13_loop
		CMP r6, r2
		BGE task13_end

		;*(gPtrArray13c + i) = *(gPtrArray11c) + *(gPtrArray11c+1)
		LDR r4, [r0]
		LDR r5, [r0, #1]
		ADD r4, r5
		STRB r4, [r1, r6, LSL #1]

		    ;gPtrArray11c++
		ADD r0, #1
		ADD r6, #1
		B	task13_loop
task13_end
        POP  {r4-r6, pc}
        ENDP


task14  PROC
		PUSH{r4-r5, lr}
        ;task14(gPtrArray12a, gPtrArray14a, gVar1);
        SUB r2, #1
		MOV r4, #0
task14_loop
        CMP  r4, r2
        BGE  task14_end

        ;uint32_t temp = *(gPtrArray12c);
        ;*(gPtrArray14c + i) = temp + 8 * (*(++gPtrArray12c));
        LDRSH  r3, [r0]
        LDRSH  r5, [r0, #2]!
        ADD  r3, r5, LSL #3
        STR  r3, [r1, r4, LSL #2]
        ADD  r4, #1
        B    task14_loop
task14_end
        POP  {r4-r5, pc}
        ENDP


task15  PROC
        PUSH {r4-r6, lr}

        ;task15(gPtrArray13a, gPtrArray15a, gVar1);
        SUB r2, #1 ; gVar1 -= 1
		MOV r6, #0 ; i = 0
task15_loop
		CMP r6, r2;	; i - gVar1
		BGE task15_end	; >=0 end loop

        ;uint32_t temp = *(gPtrArray13c++);
        ;*(gPtrArray15c + i) = temp + 16 * (*gPtrArray13c);
		LDRH r4, [r0]
		ADD r0, #2
		LDRH r5, [r0]
        LSL r5, #4
		ADD r4, r5
		STR r4, [r1 , r6, LSL #2]

		ADD r6, #1
		B 	task15_loop
task15_end
        POP  {r4-r6, pc}
        ENDP

        END
