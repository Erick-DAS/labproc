
#include <stdint.h>
#include <stdlib.h>
#include "bcm.h"

/**
 * Configura um GPIO.
 * @param gpio Índice do GPIO.
 * @param func Função desejada (INPUT, OUTPUT, ALT0, ... ALT5)
 */
void gpio_init(unsigned gpio, int func) {
   if(gpio > 53) return;
   int a = 3 * (gpio % 10);
   int b = gpio / 10;
   int c = GPIO_REG(gpfsel[b]);
   int mask = 0x07 << a;
   GPIO_REG(gpfsel[b]) = (c & (~mask)) | (func << a);
}

/**
 * Muda o estado de um GPIO de saída.
 * @param gpio Índice do GPIO.
 * @param valor Valor para a saída (0 = desligado, 1 = ligado).
 */
void gpio_put(unsigned gpio, int valor) {
   if(gpio > 53) return;
   if(valor) {
      if(gpio < 32) GPIO_REG(gpset[0]) = (1 << gpio);
      else GPIO_REG(gpset[1]) = (1 << (gpio-32));
   } else {
      if(gpio < 32) GPIO_REG(gpclr[0]) = (1 << gpio);
      else GPIO_REG(gpclr[1]) = (1 << (gpio-32));
   }
}

/**
 * Lê o estado de um GPIO de entrada.
 * @param gpio Índice do GPIO.
 * @param Valor atual da entrada.
 */
int gpio_get(unsigned gpio) {
   if(gpio > 53) return 0;
   if(gpio < 32) return GPIO_REG(gplev[0]) & (1 << gpio);
   else return GPIO_REG(gplev[1]) & (1 << (gpio-32));
}

/**
 * Troca o estado de um GPIO de saída.
 * @param gpio Índice do GPIO.
 */
void gpio_toggle(unsigned gpio) {
   if(gpio > 53) return;
   gpio_put(gpio, !gpio_get(gpio));
}

/**
 * Configura resistores de pull-up ou pull-down em uma GPIO.
 * @param gpio Índice do GPIO.
 * @param pull PULL_NONE, PULL_UP ou PULL_DOWN
 */
void gpio_set_pulls(unsigned gpio, int pull) {
   GPIO_REG(gppud) = pull;
   delay(150);
   if(gpio < 32) {
      GPIO_REG(gppudclk[0]) = (1 << gpio);
      delay(150);
      GPIO_REG(gppudclk[0]) = 0;
   } else {
      GPIO_REG(gppudclk[1]) = (1 << (gpio-32));
      delay(150);
      GPIO_REG(gppudclk[1]) = 0;
   } 
}
