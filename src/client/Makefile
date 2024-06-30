CC=gcc
CCOPTS=std=gnu99
TARGET = client
BINS = $(TARGET).elf
OBJS = serial_linux.o \
	   ui.o			  \
	   sample.o

.phony: clean all

all: $(BINS)

%.elf: %.o $(OBJS)
	$(CC) -$(CCOPTS) -o $@ $^

%.o: %.c 
	$(CC) -$(CCOPTS) -c -o $@ $<

# serial_linux <serial_file> <baudrate>
run: $(BINS)
	./$(BINS) /dev/ttyUSB0 19200

clean:
	rm -rf *~ $(BINS) $(OBJS)

