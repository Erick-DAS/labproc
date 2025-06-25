
#ifndef __PI_H__
#define __PI_H__

#define GPIO_FUNC_INPUT          0
#define GPIO_FUNC_OUTPUT         1
#define GPIO_FUNC_ALT5           2
#define GPIO_FUNC_ALT4           3
#define GPIO_FUNC_ALT0           4
#define GPIO_FUNC_ALT1           5
#define GPIO_FUNC_ALT2           6
#define GPIO_FUNC_ALT3           7

#define GPIO_PULL_NONE           0
#define GPIO_PULL_DOWN           1
#define GPIO_PULL_UP             2

void delay(unsigned ciclos);
unsigned get_arm_mode(void);
void set_arm_mode(unsigned md);
unsigned get_core(void);
void enable_irq(unsigned en);
void enable_fiq(unsigned en);

void gpio_init(unsigned gpio, int func);
void gpio_put(unsigned gpio, int valor);
int gpio_get(unsigned gpio);
void gpio_toggle(unsigned gpio);
void gpio_set_pulls(unsigned gpio, int pull);

void uart_init(unsigned baud);
void uart_putc(char c);
void uart_puts(char *s);
char uart_getc(void);

#endif

