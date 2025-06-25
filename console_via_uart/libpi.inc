
.set GPIO_FUNC_INPUT, 0
.set GPIO_FUNC_OUTPUT, 1
.set GPIO_FUNC_ALT5, 2
.set GPIO_FUNC_ALT4, 3
.set GPIO_FUNC_ALT0, 4
.set GPIO_FUNC_ALT1, 5
.set GPIO_FUNC_ALT2, 6
.set GPIO_FUNC_ALT3, 7

.set GPIO_PULL_NONE, 0
.set GPIO_PULL_DOWN, 1
.set GPIO_PULL_UP,   2

.set ARM_MODE_USER, 0b10000
.set ARM_MODE_FIQ,  0b10001
.set ARM_MODE_IRQ,  0b10010
.set ARM_MODE_SVR,  0b10011
.set ARM_MODE_MONITOR, 0b10110
.set ARM_MODE_ABORT, 0b10111
.set ARM_MODE_UNDEF, 0b11011
.set ARM_MODE_HYPER, 0b11010
.set ARM_MODE_SYSTEM, 0b11111

/*****************************************************************
 * Funções de libpi.a:
 ***
 * delay 
 * -- parâmtros: r0 (tempo)
 * -- retorno: -
 * Espera r0 loops vazios
 ***
 * get_arm_mode 
 * -- parâmtros: -
 * -- retorno: r0 (modo atual ARM_MODE_....))
 * Lê o modo do processador no registrador cpsr
 ***
 * set_arm_mode 
 * -- parâmtros: r0 (modo desejado)
 * -- retorno -
 * Muda o modo do processador (ARM_MODE...)
 ***
 * get_core 
 * -- parâmtros: -
 * -- retorno r0 (Índice do núcleo atual (afinidade))
 * Identifica o núcleo (0 a 3) que está executando.
 ***
 * get_lock
 * -- parâmetros: r0 (endereço da tranca a obter)
 * --             r1 (valor a escrever, diferente de zero).
 * -- retorno: -
 * Obtém uma trava de acesso exclusivo (spinlock).
 ***
 * put_lock
 * -- parâmetros: r0 (endereço da tranca a liberar)
 * -- retorno: -
 * Libera uma trava de acesso exclusivo (spinlock).
 ***
 * enable_irq 
 * -- parâmtros: r0 (booleano habilita ou desabilita)
 * -- retorno -
 * Habilita ou desabilita as interrupções normais.
 ***
 * enable_fiq 
 * -- parâmtros: r0 (booleano habilita ou desabilita)
 * -- retorno -
 * Habilita ou desabilita as interrupções rápidas.
 ***
 * gpio_init 
 * -- parâmtros: r0 (índice do GPIO, de 0 a 53)
 * --            r1 (função desejada GPIO_FUNC_...)
 * -- retorno -
 * Configura um GPIO antes do uso.
 ***
 * gpio_put 
 * -- parâmtros: r0 (índice do GPIO, de 0 a 53)
 * --            r1 (valor a escrever, 0 ou 1)
 * -- retorno -
 * Altera o valor de um GPIO configurado como saída
 ***
 * gpio_get 
 * -- parâmtros: r0 (índice do GPIO, de 0 a 53)
 * -- retorno r0 (valor atual do GPIO)
 * Lê o estado atual de um GPIO
 ***
 * gpio_toggle 
 * -- parâmtros: r0 (índice do GPIO, de 0 a 53)
 * -- retorno -
 * Alterna o estado de um GPIO configurado como saída.
 ***
 * gpio_set_pulls 
 * -- parâmtros: r0 (índice do GPIO, de 0 a 53)
 * --            r1 (configuração de pull-up (GPIO_PULL_...))
 * -- retorno -
 * Configura os resistores internos conectados a um GPIO.
 ***
 * uart_init 
 * -- parâmtros: r0 (baudrate (por exemplo, 9600))
 * -- retorno -
 * Configura a uart antes de sua utilização.
 ***
 * uart_putc 
 * -- parâmtros: r0 (caractere a enviar)
 * -- retorno -
 * Envia um byte através da uart
 ***
 * uart_puts 
 * -- parâmtros: r0 (ponteiro para um string C)
 * -- retorno -
 * Envia um string terminado por zero através da uart.
 ***
 * uart_getc 
 * -- parâmtros: -
 * -- retorno Valor do caractere recebido
 * Lê um byte através da uart.
 ****************************************************************/
