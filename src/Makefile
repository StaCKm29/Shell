# Variables
CC = gcc
CFLAGS = -Wall -Wextra

# Reglas

shell: main.o
    $(CC) $(CFLAGS) -o shell main.o

main.o: main.c tokenPipes.c ejecutarComandos.c tokenEspacios.c alarma.c favs.c 
    $(CC) $(CFLAGS) -c main.c

.PHONY: clean
clean: 
    rm -f *.o shell