CC=gcc
CFLAGS=-lrt -pthread -Wall -Wextra -pedantic
OBJ = server.o client.o servant.o
DEPS = hdr.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ server.c $(CFLAGS)
	$(CC) -o client client.c $(CFLAGS)
	$(CC) -o servant servant.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 