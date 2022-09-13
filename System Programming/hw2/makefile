CC=gcc
CFLAGS=-Wall 
OBJ = processP.o covarianceMatrix.o
DEPS = hdr.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

processP: $(OBJ)
	$(CC) -o $@ processP.c $(CFLAGS) -lm
	$(CC) -o covarianceMatrix covarianceMatrix.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 