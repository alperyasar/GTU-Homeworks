CC=gcc
CFLAGS=-Wall -pthread -lrt
OBJ = hw4.o
DEPS = hdr.h

%.o: %.c $(DEPS)
	> /tmp/sem-mutex-key
	> /tmp/sem-buffer-count-key
	> /tmp/sem-spool-signal-key
	$(CC) -c -o $@ $< $(CFLAGS)

hw4: $(OBJ)
	$(CC) -o $@ hw4.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
