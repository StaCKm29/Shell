#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Maneja el comando ingresado, eliminando espacios y ejecutando el comando.
 * @param comando: la cadena de caracteres que contiene el comando a ejecutar.
 * @return args: arreglo de punteros que apuntan a los argumentos (char).
 */
char** tokenEspacios(char *comando) {
    char **args = malloc(1024 * sizeof(char*));
    char *token = strtok(comando, " "); // strtok divide la cadena en tokens, en este caso, por espacios.
    int i = 0;

    while (token != NULL) { // Mientras aún hayan tokens.
        args[i++] = token; // Arreglo de solo argumentos.
        token = strtok(NULL, " "); // Para obtener el siguiente token.
    }
    args[i] = NULL; // El último argumento es NULL.

    return args;
}
