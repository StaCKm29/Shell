# Nombre del ejecutable
EXEC = shell

# Archivos fuente
SRC = main.c tokenPipes.c ejecutarComandos.c tokenEspacios.c alarma.c favs.c

# Compilador y banderas
CC = gcc
CFLAGS = -Wall -Wextra -g

# Archivos objeto
OBJ = $(SRC:.c=.o)

# Regla por defecto
all: $(EXEC)

# Regla para generar el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regla para generar los archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
