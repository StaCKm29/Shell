#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
* Elimina todos los espacios de la cadena de caracteres que contiene el o los comandos a ejecutar
 * Lo hace a traves de tokens
 * @param comando : la cadena de caracteres que contiene el comando a ejecutar. *comando es el puntero hacia esta cadena.
 */
void tokenEspacios(char *comando) {
    char *args[1024]; //Arreglo de 1024 punteros que apuntan a los argumentos (char).
    char *token = strtok(comando, " "); //strtok divide la cadena en tokens, en este caso, por espacios.
    int i = 0;

    while (token != NULL) { //Mientras aún hayan tokens.
        args[i++] = token; //Arreglo de solo argumentos.
        token = strtok(NULL, " "); //Para obtener el siguiente token.
    }
    args[i] = NULL; //El último argumento es NULL.

    execvp(args[0], args); //Ejecuta el o los comandos una vez que solo se tengan las instrucciones.

    //Imprime un mensaje de error. Solo si no se pudo concretar el execvp. De lo contrario no se pasa por aqui.
    perror("Error al ejecutar el comando.\n");
    exit(1);
}