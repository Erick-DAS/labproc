.section .c
	c: .string "carlos barbara elias"

.section .pascal
	pascal: .string ""

.text
	.global _start
	
	_start:
		ldr r0, =c 		;@ Endereço do primeiro byte da string em C
		ldr r1, =pascal
		mov r5, #255    ;@ 255 (tamanho máxima da string em pascal)
		mov r4, #0x0    ;@ 0
		mov r2, #0x0    ;@ Contador, inicializado com 0
		mov r6, #0      ;@ Registrador auxiliar (inicializado com 0 para ser restaurado com 0 dentro da sub rotina e evitar warning de clobbered
		bl c_to_pascal
		;@ bl pascal_to_c
		b finish

	c_to_pascal:
		ldrb r3, [r0, r2] ;@ r3 recebe valor do endereço [r1 + r2]
		cmp r2, r5        ;@ Verifica se tamanho da string chegou a 255
		beq .loop_end_ctp
		cmp r3, r4        ;@ Verifica se o byte lido é o caracter nulo (fim da string)
		beq .loop_end_ctp
		add r2, r2, #1    ;@ Incrementa o tamanho da string
		strb r3, [r1, r2] ;@ Salva o byte no endereço da string pascal
		b c_to_pascal

	.loop_end_ctp:
		strb r2, [r1]    ;@ Salva o tamanho da string no endereço r1
		bx lr

	pascal_to_c:
		ldrb r3, [r1] ;@ r3 recebe o tamanho da string
		mov r2, #0    ;@ Inicializa o contador com 0

	.loop_ptc:
		cmp r2, r3        ;@ Verifica se o contador atingiu o tamanho da string
		beq .loop_end_ptc
		add r2, r2, #1    ;@ Incrementa o contador para fazer o load
		ldrb r6, [r1, r2] ;@ Load do byte da string pascal
		sub r2, r2, #1    ;@ Decrementa o contador para fazer o store
		strb r6, [r0, r2] ;@ Store do byte na string c
		add r2, r2, #1    ;@ Incrementa o contador
		b .loop_ptc

	.loop_end_ptc:
		strb r4, [r0, r2] ;@ Salva o caracter nulo
		mov r6, #0        ;@ Restaura o valor de r6
		bx lr

	finish:
		b finish
