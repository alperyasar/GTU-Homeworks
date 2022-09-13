CC=gcc
CFLAGS=-Wall 
OBJ = hw1.o
DEPS = hdr.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hw1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 