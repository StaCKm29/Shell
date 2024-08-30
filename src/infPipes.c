#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

const int READ = 0;  // Variable de lectura para pipe
const int WRITE = 1; // Variable de escritura para pipe
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

void ejecutarComandos(char **comandos, int num_comandos) {
    //si fueran tres comandos separados por dos pipes, entonces el arreglo seria [4], es decir,
    //num_comandos - 1 = 2 y eso multiplicado por 2 es 4.
    int mispipes[2 * (num_comandos - 1)], i;

    for (i = 0; i < num_comandos - 1; i++) {
        if(pipe(mispipes + i * 2) < 0) {
            perror("Error creando pipe.\n");
            exit(1);
        }
        //se crea el pipe
    }

    pid_t pid;
    for(i = 0; i < num_comandos; i++) {
        pid = fork();
        if (pid == 0) {
            //Redireccionar la entrada del proceso.
            if(i>0) { //Solo si el proceso actual no es el primer comando.
                if(dup2(mispipes[(i-1) * 2], READ) < 0) { //dup2() retorna -1 si hay error.
                    perror("Error duplicando descriptor de archivo (fd) para entrada.\n");
                    exit(1);
                }
                //se duplica el descriptor de archivo para la entrada. (else)
            }

            //Redireccionar la salida del proceso.
            if (i < num_comandos-1) { //Solo si el proceso actual no es el último comando.
                if(dup2(mispipes[i * 2 + 1], WRITE) < 0) {
                    perror("Error duplicando descriptor de archivo (fd) para salida.\n");
                    exit(1);
                }
                //se duplica el descriptor de archivo para la salida. (else)
            }

            // Cerrar todos los pipes en el proceso hijo
            for (int j = 0; j < 2 * (num_comandos - 1); j++) {
                close(mispipes[j]);
            }

            tokenEspacios(comandos[i]);
        } else if (pid < 0) {
            perror("Error en fork()");
            exit(1);
        }
    }

    // Cerrar todos los pipes en el proceso padre
    for (i = 0; i < 2 * (num_comandos - 1); i++) {
        close(mispipes[i]);
    }

    // Esperar a que todos los hijos terminen
    int status; //para guardar el estado de salida de los hijos.
    for (i = 0; i < num_comandos; i++) {
        pid_t child_pid = waitpid(-1, &status, 0);
        if (child_pid < 0) {
            perror("Error esperando proceso hijo");
            exit(1);
        }
    }
}

int main() {
    char input[1024] = "ls -l | grep .c | wc"; //input de prueba
    char **comandos = malloc(1024 * sizeof(char *)); //dinamico
    int num_comandos;

    // Dividir la entrada por pipes
    tokenPipes(input, &comandos, &num_comandos);
    // Ejecutar los comandos divididos por pipes
    ejecutarComandos(comandos, num_comandos);

    free(comandos); //libera la memoria.
    return 0;
}
