.include "libpi.inc"

/*
 * O led verde do RPi 2 é o GPIO 47
 */
.set LED, 47

.text
.global start
start:
  /*
   * RITUAL OBRIGATÓRIO -- FAVOR NÃO TENTAR ENTENDER
   * Verifica priviégio de execução EL2 (HYP) ou EL1 (SVC)
   */
  mrs r0, cpsr
  and r0, r0, #0x1f
  cmp r0, #0x1a
  bne continua


  /*
   * Sai do modo EL2 (HYP)
   */
  mrs r0, cpsr
  bic r0, r0, #0x1f
  orr r0, r0, #0x13
  msr spsr_cxsf, r0
  add lr, pc, #4       // aponta o rótulo 'continua'
  msr ELR_hyp, lr
  eret                 // 'retorna' do privilégio EL2 para o EL1

continua:
  /*
   * Verifica o índice das CPUs
   */
  bl get_core
  cmp r0, #0
  beq core0

// Núcleos #1, #2 e #3 vão executar a partir daqui

trava:
  wfe
  b trava

// Execução do núcleo #0
core0:
  /*
   * INICIALIZAÇÃO
   * configura os stack pointers
   */
  mov r0, #0x13     // Modo SVC
  msr cpsr_c,r0
  ldr sp, =stack_addr

 /*
  * Aqui finalmente começa o programa
  */

  mov r0, #LED   
  mov r1, #GPIO_FUNC_OUTPUT
  bl gpio_init

setup:
    mov r6, #0 @ Zerando o registrador que será o contador de zeros
    mov r4, #0b00010000000000000000000000000000 @ Inserindo o valor a ser verificado

loop:
    lsr r2, r4, #31 @ Isolando o MSB do número
    cmp r2, #0 @ Comparando o MSB com zero
    addeq r6, r6, #1 @Soma um no registrador caso a comparação anterior ative a flag de igualdade
    lsl r4, r4, #1 @ Faz um shift para a esquerda no r1 para remover o bit já analisado
    cmp r2, #1 @ Se r2 for 1, encontramos o primeiro 1 e encerra o programa
    bne loop

loop_pisca: 
    cmp r6, #0
    beq end
    b pisca 
    b loop_pisca


 /*
  * pisca o led indefinidamente
  */
pisca:
   mov r0, #LED
   mov r1, #1
   bl gpio_put
   ldr r0, =1000000
   bl delay

   mov r0, #LED
   mov r1, #0
   bl gpio_put

   ldr r0, =1000000
   bl delay
   add r6, r6, #-1
   b loop_pisca

end:
    b end
