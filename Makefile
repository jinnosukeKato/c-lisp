CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

lisp: $(OBJS)
				$(CC) -o lisp $(OBJS) $(LDFLAGS)

$(OBJS): lisp.h

tmp.s: lisp
				./lisp "(add (5 5))" > tmp.s

tmp.elf: compile
				$(CC) tmp.s -o tmp.elf

compile: tmp.s

assembly: tmp.elf

run: assembly
				 ./tmp.elf

clean:
				rm -f lisp *.o *~ tmp* *.elf

.PHONY: clean compile assembly run
