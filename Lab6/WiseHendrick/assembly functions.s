        AREA my_fancy_asm_code, CODE, READONLY   ; Define the program area
        
        ; Export functions defined in this file. These functions need to be declared 
        ; in the file calling them.
        EXPORT task10
        EXPORT task11
        EXPORT task12
        EXPORT task13
        EXPORT task14
        EXPORT task15

        IMPORT gPtrArray10a
        IMPORT gPtrArray11a
        IMPORT gPtrArray12a
        IMPORT gPtrArray13a
        IMPORT gPtrArray14a
        IMPORT gPtrArray15a
        IMPORT gVar1
            
        ALIGN                   ; Align the data in the boundary of 4 bytes. 
           
task10  PROC
        MOV  r2, #0             ; variable (int) i
task10_loop
        CMP  r2, r1                 ; test = r2 - r1
        BGE  task10_end             ; if test >= 0, then branch to task10_end    
        MOV  r3, r2, LSL #2         ; r3 <- r2 * 4
        SUB  r3, #15                ; r3 <- r3 - 15
        STRB r3, [r0, r2]           ; r3 -> mem[r0 + r2] or r3 -> mem[r0 + i]
        ADD  r2, #1                 ; r2 <- r2 + 1
        B    task10_loop            ; branch to task10_loop
task10_end
        BX   lr                     ; return
        ENDP
			
task11  PROC  
		MOV  r2, #0             ; variable (int) i
task11_loop
        CMP  r2, r1         	; test = r2 - r1
        BGE  task11_end         ; if test >= 0, then branch to task11_end    
        MOV  r3, r2, LSL #5     ; r3 = r2 * 32
        ADD  r3, #2             ; r3 += 2
        STRB r3, [r0, r2]       ; gPtrArray11a[i] = r3
        ADD  r2, #1             ; i++
        B    task11_loop        ; branch to task11_loop
task11_end
        BX   lr     
        ENDP

task12  PROC
        PUSH {r4-r5, lr}			
        MOV  r4, #0           
task12_loop
        CMP  r4, r2					; test i
        BGE  task12_end  			; test i
        LDRSB  r5, [r0, r4]			; r5 = gPtrArray10a[i]
        LDR  r3, =10				; r3 = 10;
        SUB  r3, r5					; r3 -= r5
        STRH r3, [r1, r4, LSL #1]	; gPtrArray12a[2*i] = r3
        ADD  r5, #1					; r5++
        STRB r5, [r0, r4]			; gPtrArray10a[i] = r5
        ADD  r4, #1					; i++
        B    task12_loop
task12_end
        POP  {r4-r5, pc}       ; Pop lr to pc, which is the same as BX lr.
        ENDP
        
task13  PROC
        PUSH {r4-r5, lr}		
		SUB  r2, #1
        MOV  r3, #0           
task13_loop
        CMP  r3, r2					; check i
        BGE  task13_end				; check i
		LDRB r4, [r0]				; r4 = gPtrArray11a
		LDRB r5, [r0, #1]			; r5 = gPtrArray11a + 1
		ADD r4, r5 					; r4 += r5
		STRH r4, [r1, r3, LSL #1]	; gPtrArray13a[2 * i] = r4
		ADD  r0, #1					; gPtrArray11a ++
	    ADD  r3, #1					; i++
        B    task13_loop
task13_end
        POP  {r4-r5, pc}
        ENDP
    
task14  PROC
        PUSH {r4-r5, lr}
        SUB  r2, #1
        MOV  r3, #0            
task14_loop
        CMP  r3, r2					; check i
        BGE  task14_end  			; Check i
        LDRSH  r4, [r0]				; r4 = gPtrArray12a
        LDRSH  r5, [r0, #2]!        ; r5 = *(++gPtrArray12a)
        ADDS  r4, r5, LSL #3		; r4 += 8 * r5
        STR  r4, [r1, r3, LSL #2]   ; gPtrArray14a[2*i] = r4 
        ADD  r3, #1					; i++
        B    task14_loop
task14_end
        POP  {r4-r5, pc}
        ENDP

task15  PROC
        PUSH {r4-r5, lr}
        SUB  r2, #1
        MOV  r3, #0
task15_loop
        CMP  r3, r2                	; check i
        BGE  task15_end            	; check i
        LDRH r4, [r0], #2          	; r4 = *(gPtrArray13a++)
        LDRH r5, [r0]             	; r5 = *gPtrArray13a
        LSL  r5, #4					; r5 *= 16
		ADD  r5, r4            		; r5 += r4
        STR  r5, [r1 , r3, LSL #2]  ; gPtrArray15a[i] = r5;
        ADD  r3, #1                	; i++
        B    task15_loop
task15_end
        POP  {r4-r5, pc}
        ENDP
	
		END