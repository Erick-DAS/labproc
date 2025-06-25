
#ifndef __BCM_H__
#define __BCM_H__

#include <stdint.h>

#define SYSCLOCK_HZ  250000000
#define APBCLOCK_HZ  125000000
/*
 * Macros úteis
 */
#define __bit(X)             (0x01 << X)
#define bit_is_set(X, Y)     (X & (0x01 << Y))
#define bit_not_set(X, Y)    ((X & (0x01 << Y)) == 0)
#define set_bit(X, Y)        X |= __bit(Y)
#define clr_bit(X, Y)        X &= (~__bit(Y))

/*
 * Endereços dos periféricos
 */
#ifndef RPICPU
#error Versão do Raspberry pi não definida
#endif

#if RPICPU == 2
#define PERIPH_BASE  0x3f000000
#elif RPICPU == 0
#define PERIPH_BASE  0x20000000
#else
#endif

#define GPIO_ADDR    (PERIPH_BASE + 0x200000)
#define AUX_ADDR     (PERIPH_BASE + 0x215000)
#define AUX_MU_ADDR  (PERIPH_BASE + 0x215040)
#define TIMER_ADDR   (PERIPH_BASE + 0x00B400)
#define IRQ_ADDR     (PERIPH_BASE + 0x00B200)
#define GPU_MAILBOX_ADDR (PERIPH_BASE + 0x00B880)

#define CORE_ADDR    0x40000000

/*
 * Periférico GPIO
 */
typedef struct {
   volatile uint32_t gpfsel[6];   // Function select (3 bits/gpio)
   unsigned : 32;
   volatile uint32_t gpset[2];    // Output set (1 bit/gpio)
   unsigned : 32;
   volatile uint32_t gpclr[2];    // Output clear (1 bit/gpio)
   unsigned : 32;
   volatile uint32_t gplev[2];    // Input read (1 bit/gpio)
   unsigned : 32;
   volatile uint32_t gpeds[2];    // Event detect status
   unsigned : 32;
   volatile uint32_t gpren[2];    // Rising-edge detect enable
   unsigned : 32;
   volatile uint32_t gpfen[2];    // Falling-edge detect enable
   unsigned : 32;
   volatile uint32_t gphen[2];    // High level detect enable
   unsigned : 32;
   volatile uint32_t gplen[2];    // Low level detect enable
   unsigned : 32;
   volatile uint32_t gparen[2];   // Async rising-edge detect
   unsigned : 32;
   volatile uint32_t gpafen[2];   // Async falling-edge detect
   unsigned : 32;
   volatile uint32_t gppud;       // Pull-up/down enable
   volatile uint32_t gppudclk[2]; // Pull-up/down clock enable
} gpio_reg_t;
#define GPIO_REG(X)  ((volatile gpio_reg_t*)(GPIO_ADDR))->X

/*
 * Periférico AUX
 */
typedef struct {
   volatile uint32_t irq;
   volatile uint32_t enables;
} aux_reg_t;
#define AUX_REG(X)   ((volatile aux_reg_t*)(AUX_ADDR))->X

/*
 * AUX/Mini UART
 */
typedef struct {
   volatile uint32_t io;
   volatile uint32_t ier;
   volatile uint32_t iir;
   volatile uint32_t lcr;
   volatile uint32_t mcr;
   volatile uint32_t lsr;
   volatile uint32_t msr;
   volatile uint32_t scratch;
   volatile uint32_t cntl;
   volatile uint32_t stat;
   volatile uint32_t baud;
} mu_reg_t;
#define MU_REG(X)    ((volatile mu_reg_t*)(AUX_MU_ADDR))->X

/*
 * Timer
 */
typedef struct {
   volatile uint32_t load;
   volatile uint32_t value;
   volatile uint32_t control;
   volatile uint32_t ack;
   volatile uint32_t raw_irq;
   volatile uint32_t masked_irq;
   volatile uint32_t reload;
   volatile uint32_t pre;
   volatile uint32_t counter;
} timer_reg_t;
#define TIMER_REG(X)   ((volatile timer_reg_t*)(TIMER_ADDR))->X

/*
 * Controlador de interrupções.
 */
typedef struct {
   volatile uint32_t pending_basic;
   volatile uint32_t pending_1;
   volatile uint32_t pending_2;
   volatile uint32_t fiq;
   volatile uint32_t enable_1;
   volatile uint32_t enable_2;
   volatile uint32_t enable_basic;
   volatile uint32_t disable_1;
   volatile uint32_t disable_2;
   volatile uint32_t disable_basic;
} irq_reg_t;
#define IRQ_REG(X)     ((volatile irq_reg_t*)(IRQ_ADDR))->X

/*
 * Controlador de DMA
 */
typedef struct {
   volatile uint32_t ti;
   volatile uint32_t saddr;
   volatile uint32_t daddr;
   volatile uint32_t length;
   volatile uint32_t stride;
   volatile uint32_t nextcb;
   unsigned : 32;
   unsigned : 32;
} dma_cb_t;

typedef struct {
   volatile uint32_t cs;
   volatile uint32_t cb;
   volatile uint32_t ti;
   volatile uint32_t saddr;
   volatile uint32_t daddr;
   volatile uint32_t length;
   volatile uint32_t stride;
   volatile uint32_t nextcb;
   volatile uint32_t debug;
} dma_reg_t;
#define DMA_CHN_REG(X,Y)  ((volatile dma_reg_t*)(DMA ## X ## _ADDR))->Y
#define DMA_STATUS_REG (*(volatile uint32_t*)DMA_STATUS_ADDR)
#define DMA_ENABLE_REG (*(volatile uint32_t*)DMA_ENABLE_ADDR)


/*
 * Mailboxes
 */
typedef struct {
   volatile uint32_t control;
   unsigned : 32; 
   volatile uint32_t timer_pre;
   volatile uint32_t irq_routing;
   volatile uint32_t pmu_irq_enable;
   volatile uint32_t pmu_irq_disable;
   unsigned : 32;
   volatile uint32_t timer_count_lo;
   volatile uint32_t timer_count_hi;
   volatile uint32_t local_routing;
   unsigned : 32;
   volatile uint32_t axi_counters;
   volatile uint32_t axi_irq;
   volatile uint32_t timer_control;
   volatile uint32_t timer_flags;
   unsigned : 32;
   volatile uint32_t timer_irq[4];
   volatile uint32_t mailbox_irq[4];
   volatile uint32_t irq_source[4];
   volatile uint32_t fiq_source[4];
   volatile uint32_t core0_mailbox_write[4];
   volatile uint32_t core1_mailbox_write[4];
   volatile uint32_t core2_mailbox_write[4];
   volatile uint32_t core3_mailbox_write[4];
   volatile uint32_t core0_mailbox_read[4];
   volatile uint32_t core1_mailbox_read[4];
   volatile uint32_t core2_mailbox_read[4];
   volatile uint32_t core3_mailbox_read[4];
} core_reg_t;
#define CORE_REG(X)     ((volatile core_reg_t*)(CORE_ADDR))->X

/*
 * Interface com a GPU
 */
typedef struct {
   volatile uint32_t read;
   unsigned : 32;
   unsigned : 32;
   unsigned : 32;
   volatile uint32_t poll;
   volatile uint32_t sender;
   volatile uint32_t status;
   volatile uint32_t config;
   volatile uint32_t write;
} gpumail_reg_t;
#define GPUMAIL_REG(X)     ((volatile gpumail_reg_t*)(GPU_MAILBOX_ADDR))->X

#endif
