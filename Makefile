CC=msp430-gcc
CFLAGS=-Os -Wall -g -mmcu=msp430g2231 -nostdlib
OBJS=main.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o main.elf $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

program: all
	sudo mspdebug rf2500 "prog main.elf"

clean:
	rm -fr main.elf $(OBJS)
