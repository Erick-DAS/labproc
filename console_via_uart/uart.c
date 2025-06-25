
#include "bcm.h"
#include "pi.h"

/**
 * Inicia a uart 1 (GPIO 14 e 15, ALT-5)
 */
void uart_init(unsigned baud) {
   /*
    * Configura os pinos
    */
   gpio_init(14, GPIO_FUNC_ALT5);
   gpio_init(15, GPIO_FUNC_ALT5);
   gpio_set_pulls(14, GPIO_PULL_UP);
   gpio_set_pulls(15, GPIO_PULL_UP);

   /*
    * Configura o periférico auxiliar
    */
   baud = 31250000 / baud;    // considerando clock de 250 MHz

   set_bit(AUX_REG(enables), 0);
   MU_REG(cntl) = 0;
   MU_REG(ier) = 0;
   MU_REG(lcr) = 3;           // 8 bits
   MU_REG(mcr) = 0;
   MU_REG(baud) = baud-1;     // baudrate
   MU_REG(cntl) = 3;          // habilita TX e RX
}

/**
 * Envia um caractere pela uart
 */
void uart_putc(char c) {
   while((MU_REG(lsr) & 0x20) == 0) ;
   MU_REG(io) = c;
}

/**
 * Envia um string pela uart
 */
void uart_puts(char *s) {
   while(*s) {
      uart_putc(*s);
      s++;
   }
}

/**
 * Recebe um caractere pela uart
 */
char uart_getc(void) {
   while((MU_REG(lsr) & 0x01) == 0) ;
   return MU_REG(io);
}

