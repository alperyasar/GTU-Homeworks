CC=gcc
CFLAGS=-Wall 
OBJ = client.o serverZ.o serverY.o
DEPS = hdr.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

client: $(OBJ)
	$(CC) -o $@ client.c $(CFLAGS)
	$(CC) -o serverZ serverZ.c $(CFLAGS) -lrt
	$(CC) -o serverY serverY.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 