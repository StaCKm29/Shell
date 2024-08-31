#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Maneja el comando ingresado, eliminando espacios y ejecutando el comando.
 * @param comando: la cadena de caracteres que contiene el comando a ejecutar.
 */
void tokenEspacios(char *comando) {
    char *args[1024]; // Arreglo de 1024 punteros que apuntan a los argumentos (char).
    char *token = strtok(comando, " "); // strtok divide la cadena en tokens, en este caso, por espacios.
    int i = 0;

    while (token != NULL) { // Mientras aún hayan tokens.
        args[i++] = token; // Arreglo de solo argumentos.
        token = strtok(NULL, " "); // Para obtener el siguiente token.
    }
    args[i] = NULL; // El último argumento es NULL.

    // Ejecuta el comando utilizando execvp.
    execvp(args[0], args);

    // Imprime un mensaje de error. Solo si no se pudo concretar el execvp.
    perror("Error al ejecutar el comando.\n");
    exit(1);

}
