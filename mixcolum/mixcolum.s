.data 

text_input:
    .byte 0x00, 0x01, 0x02, 0x03  // linha 0
    .byte 0x04, 0x05, 0x06, 0x07  // linha 1
    .byte 0x08, 0x09, 0x0A, 0x0B  // linha 2
    .byte 0x0C, 0x0D, 0x0E, 0x0F  // linha 3

.text
	.global _start
	
	_start:
		ldr r0, =text_input 		;@ Endereço do primeiro byte de text
		add r0, r0, #1
		bl MixColumn
		b finish

    ;@ r0 contem o endereço do elemento da primeira linha da coluna 
    ;@ em que se deseja aplicar a MixColumn
	MixColumn:
        mov r4, #0        ;@ r4 = 4 (número de bytes por coluna)

        add r0, r0, #12  ;@ r0 aponta para o último byte da coluna

.loopMixColumn:    ldrb r1, [r0]     ;@ Carrega o último byte da coluna em r1
        ldrb r2, [r0, #-4] ;@ Carrega o penúltimo byte da coluna em r2

        eor r3, r1, r2    ;@ r3 = r1 XOR r2
        strb r3, [r0]     ;@ Armazena o resultado de r1 XOR r2 no último byte da coluna

        sub r0, r0, #4    ;@ r0 aponta para o penúltimo byte da coluna

        add r4, r4, #1   ;@ Atualiza r4

        cmp r4, #3
        bne .loopMixColumn ;@ Se r4 for menor que 4, não faz mais nada
        bx lr


	finish:
		b finish




