CC=msp430-gcc
CFLAGS=-Wall -mmcu=msp430g2553 -mdisable-watchdog
OBJS=main.c

all:
	$(CC) $(CFLAGS) $(OBJS)

program: all
	sudo mspdebug rf2500 "prog a.out"

erase:
	sudo mspdebug rf2500 "erase"

run: program
	sudo mspdebug rf2500 "run a.out"

clean:
	rm -fr a.out
