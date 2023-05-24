CC = gcc
CFLAGS = -Wall
LIBS = image.c filtros.c processadordeimagem.c
OUT = processadordeimagem
all:
	$(CC) $(CFLAGS) -o $(OUT) $(LIBS)


clean:
	rm -f processadordeimagem 

purge: clean
	rm -f *.o
