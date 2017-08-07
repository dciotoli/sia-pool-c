# Use gcc as compiler
CC=gcc
# CFlags (remove -g later)
CFLAGS=-g -Wall -Wextra -Wundef -Wshadow -O -Werror
SRCDIR=src

all: stratum-c

stratum-c: stratum-server.o
	$(CC) $(CFLAGS) -o stratum-c stratum-server.o stratum_protocol.o

stratum-server.o: $(SRCDIR)/stratum-server.c $(SRCDIR)/stratum-server.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/stratum-server.c

stratum-protocol.o: $(SRCDIR)/stratum-protocol.c $(SRCDIR)/stratum-protocol.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/stratum-protocol.c
	
clean:
	rm stratum-c *.o