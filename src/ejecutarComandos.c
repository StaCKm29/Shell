#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **tokenEspacios(char *comando);

const int READ = 0;  // Variable de lectura para pipe
const int WRITE = 1; // Variable de escritura para pipe


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
        char **args = tokenEspacios(comandos[i]); //obtener los argumentos del comando.

        if (strcmp(args[0], "cd") == 0) {
            // Si no hay argumento para cd, cambiar al directorio home
            if (args[1] == NULL || strcmp(args[1], "~") == 0) {
                chdir(getenv("HOME"));
            } else {
                if (chdir(args[1]) != 0) {
                    perror("Error cambiando el directorio");
                }
                //Se cambia al directorio deseado.
            }
            free(args);
        } else {
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

                execvp(args[0], args); //ejecutar el comando.

            } else if (pid < 0) {
                perror("Error en fork()");
                exit(1);
            }
        }
    }

    // Cerrar todos los pipes en el proceso padre
    for (i = 0; i < 2 * (num_comandos - 1); i++) {
        close(mispipes[i]);
    }

    // Esperar a que todos los hijos terminen
    for (i = 0; i < num_comandos; i++) {
        wait(NULL);
    }
}

