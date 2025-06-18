
FONTES = Zero.s

# Interface serial a utilizar
TTY = /dev/ttyUSB0

# Configuração JTAG
OCD_CFG = jtag.cfg

#
# Arquivos de saída 
#
EXEC = Zero.elf
MAP = Zero.map
IMAGE = Zero.img
HEXFILE = Zero.hex
LIST = Zero.list

PREFIXO = arm-none-eabi-
LDSCRIPT = linker.ld
AS = ${PREFIXO}as
LD = ${PREFIXO}ld
GCC = ${PREFIXO}gcc
OBJCPY = ${PREFIXO}objcopy
OBJDMP = ${PREFIXO}objdump

# Para RPi Zero
#OPTS = -mfpu=vfp -march=armv6zk -mtune=arm1176jzf-s -g 

#Para PPi 2
OPTS = -march=armv7-a -mtune=cortex-a7 -g 

# para usar newlib
#LDOPTS = -L/usr/lib/arm-none-eabi/newlib -lc -lm
LDOPTS = -L. -lpi
OBJ = $(FONTES:.s=.o)
OBJETOS = $(OBJ:.c=.o)

all: ${EXEC} ${IMAGE} ${LIST} ${HEXFILE}

#
# Gerar executável
#
${EXEC}: ${OBJETOS}
	${LD} -T ${LDSCRIPT} -M=${MAP} -o $@  ${OBJETOS} ${LDOPTS}

#
# Gerar imagem
#
${IMAGE}: ${EXEC}
	${OBJCPY} ${EXEC} -O binary ${IMAGE}

#
# Gerar intel Hex
#
${HEXFILE}: ${EXEC}
	${OBJCPY} ${EXEC} -O ihex ${HEXFILE}

#
# Gerar listagem
#
${LIST}: ${EXEC}
	${OBJDMP} -d ${EXEC} > ${LIST}

#
# Compilar arquivos em C
#
.c.o:
	${GCC} ${OPTS} -c -o $@ $<

#
# Montar arquivos em assembler
#
.s.o:
	${AS} -g -o $@ $<

#
# Limpar tudo
#
clean:
	rm -f *.o ${EXEC} ${MAP} ${LIST} ${IMAGE}

#
# Executar openocd
#
ocd:
	@if pgrep openocd >/dev/null ; then \
		echo "openocd já está executando" ; \
	else openocd -f ${OCD_CFG} & \
	fi

#
# Gdb via serial
#
gdb: ${EXEC}
	@if pgrep openocd >/dev/null; then \
		gdb-multiarch ${EXEC} \
			-ex "target extended-remote: 3333" \
			-ex "load"; \
		else gdb-multiarch -b 115200 ${EXEC} \
		                -ex "target remote ${TTY}" \
	                   -ex "load"; \
	fi
