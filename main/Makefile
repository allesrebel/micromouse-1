CC=msp430-gcc
CFLAGS=-Wall -mmcu=msp430g2553 -mdisable-watchdog
SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.out)

all:
	$(CC) $(CFLAGS) $(SRCS)

program: all
	sudo mspdebug rf2500 "prog a.out"

erase:
	sudo mspdebug rf2500 "erase"

run: program
	sudo mspdebug rf2500 "run a.out"

clean:
	rm -fr a.out
