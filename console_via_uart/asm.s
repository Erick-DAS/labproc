
.text
.global delay, set_arm_mode, get_arm_mode
.global get_core, enable_irq, enable_fiq
.global get_lock, put_lock, init_core
.global enable_cache

delay:
   cmp r0, #0
   moveq pc, lr
   sub r0, r0, #1
   b delay

get_arm_mode:
   mrs r0, cpsr
   and r0, r0, #0b11111
   mov pc, lr

set_arm_mode:
   mrs r1, cpsr
   bic r1, r1, #0b11111
   bic r0, r0, #0b11111
   orr r1, r1, r0
   msr cpsr, r1
   mov pc, lr

get_core:
  mrc p15,0,r0,c0,c0,5    // registrador MPIDR
  and r0, r0, #0x03
  mov pc, lr

enable_irq:
  cmp r0, #0
  beq disable_irq
  mrs r0, cpsr
  bic r0, r0, #(1 << 7)
  msr cpsr, r0
  mov pc, lr
disable_irq:
  mrs r0, cpsr
  orr r0, r0, #(1 << 7)
  msr cpsr, r0
  mov pc, lr

enable_fiq:
  cmp r0, #0
  beq disable_fiq
  mrs r0, cpsr
  bic r0, r0, #(1 << 6)
  msr cpsr, r0
  mov pc, lr
disable_fiq:
  mrs r0, cpsr
  orr r0, r0, #(1 << 6)
  msr cpsr, r0
  mov pc, lr

get_lock:
.if 0
  // usando MMU+LDREX
  ldrex r2, [r0]
  cmp r2, #0
  strexeq r2, r1, [r0]
  cmpeq r2, #0
  bne get_lock
  dmb
.else
  // usando SWP
  mov r2, r1
  swp r2, r2, [r0]
  cmp r2, #0
  beq get_lock
.endif
  mov pc, lr

put_lock:
  mov r2, #0
.if 0
  dmb
.endif
  str r2, [r0]
  mov pc, lr

init_core:
  and r0, r0, #0x03
  ldr r2, =0x400000cc
  mov r3, #-1
  str r3, [r2, r0, lsl #4]
  ldr r2, =0x4000008c
  str r1, [r2, r0, lsl #4]
  sev
  mov pc, lr

enable_cache:
   mrc p15, 0, r0, c1, c0, 0
   orr r0, r0, #0x04             // habilita cache de dados
   orr r0, r0, #0x800            // habilita previsão de desvio
   orr r0, r0, #0x1000           // habilita cache de instruções
   mcr p15, 0, r0, c1, c0, 0
   mov pc, lr

