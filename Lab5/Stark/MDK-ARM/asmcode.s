AREA asm_code, CODE, READONLY       ;
	EXPORT read_a_bit_of_a_port
	EXPORT set_a_bit_of_a_port
	EXPORT clear_a_bit_of_a_port
	
	ALIGN


;extern uint32_t read_a_bit_of_a_port(__IO uint32_t *pIDR, uint32_t pinMask)
read_a_bit_of_a_port PROC
	LDR r2, [r0]            ;
	AND r0, r1, r2          ;
	BX lr                   ;
	ENDP





;extern void set_a_bit_of_a_port(__IO uint32_t *pODR, uint32_t pinMask)
set_a_bit_of_a_port PROC
	LDR r2, [r0]            ;
	ORR r2, r1              ;
	STR r2, [r0]            ;
	BX lr                   ;
	ENDP

;extern void clear_a_bit_of_a_port(__IO uint32_t *pODR, uint32_t pinMask)
clear_a_bit_of_a_port PROC
	LDR r2, [r0]            ;
	BIC r2, r1              ;
	STR r2, [r0]            ;
	BX lr                   ;
	ENDP
	
	END                     ;
