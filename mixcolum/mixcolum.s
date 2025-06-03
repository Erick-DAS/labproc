.data 

text_input:
    .byte 0x00, 0x01, 0x02, 0x03  // linha 0
    .byte 0x04, 0x05, 0x06, 0x07  // linha 1
    .byte 0x08, 0x09, 0x0A, 0x0B  // linha 2
    .byte 0x0C, 0x0D, 0x0E, 0x0F  // linha 3

.text
	.global _start
	
	_start:
		ldr r0, =text_input 		;@ Endereço do primeiro byte de text (executa na primeira coluna)
		;@ add r0, r0, #1           ;@ Some 1 caso queira executar na segunda coluna, e assim por diante
		bl MixColumn                ;@ Chama a função MixColumn
		b finish

	MixColumn:
    ;@ r0 contem o endereço do elemento da primeira linha da coluna em que se deseja aplicar a MixColumn

        mov r4, #0        ;@ Reseta o contador
        add r0, r0, #12  ;@ r0 aponta para o último byte da coluna (processo feito de baixo para cima)

.loopMixColumn:    ldrb r1, [r0]     ;@ Carrega o último byte da coluna em r1
        ldrb r2, [r0, #-4] ;@ Carrega o penúltimo byte da coluna em r2

        eor r3, r1, r2    ;@ r3 = r1 XOR r2
        strb r3, [r0]     ;@ Armazena o resultado de r1 XOR r2 no último byte da coluna

        sub r0, r0, #4    ;@ r0 aponta para o penúltimo byte da coluna

        add r4, r4, #1    ;@ Atualiza contador

        cmp r4, #3        ;@ Fazer apenas para as 3 últimas linhas
        bx lr


	finish:
		b finish




