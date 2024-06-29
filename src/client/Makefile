CC=gcc
CCOPTS=-std=gnu99
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

# serial_linux <serial_file> <baudrate> <read=1, write=0>
run: $(BINS)
	./$(BINS) /dev/ttyUSB0 19200 1

clean:
	rm -rf *~ $(BINS) $(OBJS)

