CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
 
lisp: $(OBJS)
				$(CC) -o lisp $(OBJS) $(LDFLAGS)

$(OBJS): lisp.h

clean:
				rm -f lisp *.o *~ tmp*

.PHONY: clean
