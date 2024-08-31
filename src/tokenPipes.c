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