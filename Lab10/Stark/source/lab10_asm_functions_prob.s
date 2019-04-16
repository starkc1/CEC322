                AREA my_asm_code, CODE, READONLY   ; Define the program area
        
; Export functions defined in this file. These functions need to be declared 
; in the file calling them.
                EXPORT asm_number_of_1s_alg1
                EXPORT asm_number_of_1s_alg2
                EXPORT asm_number_of_1s_alg3
                EXPORT asm_number_of_1s_alg2_asm_caller
                EXPORT asm_number_of_1s_alg3_asm_caller
        
                ALIGN           ; Align the data in the boundary of 4 bytes. 


asm_number_of_1s_alg1   PROC
                MOV  r1, #0             ; n_of_1
alg1_lp         CBZ  r0, alg1_done
                ADD  r1, r0, LSR #31
                MOV  r0, r0, LSL #1
                B    alg1_lp
alg1_done       MOV  r0, r1
                BX   lr
                ENDP


asm_number_of_1s_alg2   PROC
                MOV  r1, r0, LSR #31    ; n_of_1
alg2_lp         CBZ  r0, alg2_done
                MOVS r0, r0, LSL #2
                ADC  r1, r0, LSR #31
                B    alg2_lp
alg2_done       MOV  r0, r1
                BX   lr
                ENDP


asm_number_of_1s_alg3   PROC
                MOV  r1, #0             ; n_of_1
alg3_lp         CBZ  r0, alg3_done
                SUB  r2, r0, #1
                AND  r0, r2
                ADD  r1, #1
                B    alg3_lp
alg3_done       MOV  r0, r1
                BX   lr
                ENDP


asm_number_of_1s_alg2_asm_caller   PROC
                PUSH {r4-r7, lr}   ; Have to save lr for calling another func
                MOV  r4, r0        ; pointer to the input array
                MOV  r5, r1        ; pointer to the output array (num of 1's)
                MOV  r6, r2        ; num of elements in the input array
                MOV  r7, #0        ; the loop-control variable i
asm_number_of_1s_alg2_asm_caller_loop
                CMP  r7, r6
                BHS  asm_number_of_1s_alg2_asm_caller_end
                LDR  r0, [r4], #4  ; POSTFIX increment
                BL   asm_number_of_1s_alg2
                STR  r0, [r5], #4
                ADD  r7, #1
                B    asm_number_of_1s_alg2_asm_caller_loop
asm_number_of_1s_alg2_asm_caller_end
                POP  {r4-r7, pc}
                ENDP


asm_number_of_1s_alg3_asm_caller   PROC
                PUSH {r4-r7, lr}   ; if you don't use these many registers, 
                MOV  r4, r0        ; pointer to the input array
                MOV  r5, r1        ; pointer to the output array (num of 1's)
                MOV  r6, r2        ; num of elements in the input array
                MOV  r7, #0        ; the loop-control variable i
                ; Note that you need to code using the PREFIX increment format
asm_number_of_1s_alg3_asm_caller_loop
				CMP r7, r6
				BHS asm_number_of_1s_alg3_asm_caller_end
				LDR r0, [r4,#4]!
				BL asm_number_of_1s_alg3
				STR r0, [r5,#4]!
				ADD r7, #1
				B asm_number_of_1s_alg3_asm_caller_loop
asm_number_of_1s_alg3_asm_caller_end
                POP  {r4-r7, pc}
                ENDP


                END                 ; End of the entire file
