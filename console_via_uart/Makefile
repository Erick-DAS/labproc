
FONTES = gpio.c uart.c asm.s console_uart.c
RPICPU = bcm2836

#
# Arquivos de saída 
#
EXEC = libpi.a
MAP = libpi.map
LIST = libpi.list

PREFIXO = arm-none-eabi-
AS = ${PREFIXO}as
LD = ${PREFIXO}ld
GCC = ${PREFIXO}gcc
OBJCPY = ${PREFIXO}objcopy
OBJDMP = ${PREFIXO}objdump

ifeq (${RPICPU}, bcm2836)
	# Raspberry Pi v.2 ou v.3
	ASMOPTIONS = -g --defsym RPICPU=2
	COPTIONS = -march=armv7-a -mtune=cortex-a7 -g -D RPICPU=2
else
	ifeq (${RPICPU}, bcm2835)
  		# Raspberry Pi v.0 ou v.1
   	ASMOPTIONS = -march=armv6zk -g --defsym RPICPU=0
   	COPTIONS = -march=armv6zk -mtune=arm1176jzf-s -g -D RPICPU=0
	endif
endif

OBJ = $(FONTES:.s=.o)
OBJETOS = $(OBJ:.c=.o)

LDOPTS = -lgcc -L/usr/lib/gcc/arm-none-eabi/9.2.1/

all: ${EXEC} ${LIST}

rebuild: clean all

#
# Gerar executável
#
${EXEC}: ${OBJETOS}
	${LD} -M=${MAP} ${OBJETOS} ${LDOPTS} -i -o $@

#
# Gerar listagem
#
${LIST}: ${EXEC}
	${OBJDMP} -std ${EXEC} > ${LIST}

#
# Compilar arquivos em C
#
.c.o:
	${GCC} ${COPTIONS} -c -o $@ $<

#
# Montar arquivos em assembler
#
.s.o:
	${AS} ${ASMOPTIONS} -o $@ $<

#
# Limpar tudo
#
clean:
	rm -f *.o ${EXEC} ${MAP} ${LIST} ${IMAGE}

