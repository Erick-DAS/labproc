.data 

text_input:
    .byte 0x00, 0x01, 0x02, 0x03  // linha 0
    .byte 0x04, 0x05, 0x06, 0x07  // linha 1
    .byte 0x08, 0x09, 0x0A, 0x0B  // linha 2
    .byte 0x0C, 0x0D, 0x0E, 0x0F  // linha 3

key:
    .byte 0x08, 0x09, 0x0A, 0x0B  // linha 2
    .byte 0x0C, 0x0D, 0x0E, 0x0F  // linha 3
    .byte 0x00, 0x01, 0x02, 0x03  // linha 0
    .byte 0x04, 0x05, 0x06, 0x07  // linha 1

.text
	.global _start
	
	_start:
		b AddKey

    AddKey:
        ldr r0, =text_input ;@ Endereço do primeiro byte de texto
        ldr r1, =key        ;@ Endereço do primeiro byte da chave
        mov r4, #0          ;@ Contador para percorrer os bytes

        b .loopAddKey

        b finish

    .loopAddKey:
        ldrb r2, [r0]    ;@ Carrega o valor do byte de texto em r2
        ldrb r3, [r1]    ;@ Carrega o valor do byte da chave em r3

        eor r2, r2, r3   ;@ r2 = r2 XOR r3
        strb r2, [r0]    ;@ Armazena o resultado no endereço apontado por r0

        add r0, r0, #1   ;@ Incrementa o endereço do texto
        add r1, r1, #1   ;@ Incrementa o endereço da chave

        cmp r4, #15      ;@ Verifica se já processou todos os 16 bytes
        add r4, r4, #1   ;@ Incrementa o contador
        bne .loopAddKey  ;@ Se não for o último byte, continua o loop

        bx lr

	finish:
		b finish
