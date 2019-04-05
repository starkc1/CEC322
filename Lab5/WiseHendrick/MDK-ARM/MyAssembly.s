	 AREA main, CODE, READONLY
	 EXPORT read_a_bit_of_a_port
	 EXPORT set_a_bit_of_a_port
	 EXPORT clear_a_bit_of_a_port
	
	 ALIGN

read_a_bit_of_a_port PROC
	LDR r2, [r0]
	AND r2, r1
	MOV r0, r2
	BX lr
	ENDP
		
		
set_a_bit_of_a_port PROC
	LDR r2, [r0]
	ORR r2, r1
	STR r2, [r0]
	BX lr
	ENDP
		
clear_a_bit_of_a_port PROC
	LDR r2, [r0]
	BIC r2, r1
	STR r2, [r0]
	BX lr
	ENDP
		
	END