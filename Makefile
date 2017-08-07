# Use gcc as compiler
CC=gcc
# CFlags (remove -g later)
CFLAGS=-g -Wall -Wextra -Wundef -Wshadow -O
SRCDIR=src

all: stratum-c

stratum-c: stratum-server.o stratum_protocol.o cJSON.o
	$(CC) $(CFLAGS) -o stratum-c stratum-server.o stratum_protocol.o cJSON.o

stratum-server.o: $(SRCDIR)/stratum-server.c $(SRCDIR)/stratum-server.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/stratum-server.c

stratum_protocol.o: $(SRCDIR)/stratum_protocol.c $(SRCDIR)/stratum_protocol.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/stratum_protocol.c

cJSON.o: $(SRCDIR)/cJSON.c $(SRCDIR)/cJSON.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/cJSON.c

clean:
	rm stratum-c *.o