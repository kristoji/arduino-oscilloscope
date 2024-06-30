TARGET=server
HEX = $(TARGET).hex
BINS=$(TARGET).elf 
OBJS=my_uart.o  \
	 adc.o		\
	 comm.o
	 
HEADERS=my_uart.h \
		server.h 

# the file below contains the actual rules
include ./avr.mk
