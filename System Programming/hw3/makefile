CC=gcc
CFLAGS=-Wall -pthread -lrt
OBJ = hw3named.o hw3unnamed.o
DEPS = hdr.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hw3named: $(OBJ)
	$(CC) -o $@ hw3named.c $(CFLAGS)
	$(CC) -o hw3unnamed hw3unnamed.c $(CFLAGS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 