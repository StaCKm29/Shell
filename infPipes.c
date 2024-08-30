#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Divide la cadena de caracteres que contiene los comandos a ejecutar por pipes.
 * Lo realiza a traves de tokens. Cada vez que encuentra "|" en la cadena, lo divide.
 * @param input : la cadena de caracteres original. *input es el puntero hacia esta cadena y asi modificarla.
 * @param comandos : contendra punteros a cada uno de los comandos. ***comandos es el puntero a un arreglo de punteros, los cuales apuntan a una cadena de caracteres.
 * @param num_comandos : Cantidad de subcomandos que se obtuvieron al subdividir la cadena original. *num_comandos es el puntero a este entero.
 */
void tokenPipes(char *input, char ***comandos, int *num_comandos) {
    *num_comandos = 0;

    //strtok divide la cadena en tokens, en este caso, por pipes.
    char *token = strtok(input, "|"); //input es la cadena que será modificada.

    while (token != NULL) {
        //Accede a la dirección de memoria de comandos y le suma el número de comandos.
        (*comandos)[*num_comandos] = token;
        (*num_comandos)++;
        token = strtok(NULL, "|"); //Para obtener el siguiente token.
    }
}

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


int main() {
    char input[1024] = "ls -l | grep .c | wc"; //input de prueba
    char **comandos = malloc(1024 * sizeof(char *)); //dinamico
    int num_comandos;

    // Dividir la entrada por pipes
    tokenPipes(input, &comandos, &num_comandos);

    free(comandos); //libera la memoria.
    return 0;
}
