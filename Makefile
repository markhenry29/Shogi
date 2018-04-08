# Variables Makefile ici.
FICHIERS = main.o piece.o liste_coups.o partie.o reserve.o
CC = gcc
CFLAGS = -Wall -ansi -pedantic
EXEC = Shogi

all: $(FICHIERS)
	$(CC) $(CFLAGS) $(FICHIERS) -o $(EXEC)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

piece.o: piece.c
	$(CC) $(CFLAGS) -c piece.c

liste_coups.o: liste_coups.c
	$(CC) $(CFLAGS) -c liste_coups.c

partie.o: partie.c
	$(CC) $(CFLAGS) -c partie.c

reserve.o: reserve.c
	$(CC) $(CFLAGS) -c reserve.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC) 
