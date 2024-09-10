#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "favs.h"
#include "alarma.h"
#include "tokenEspacios.h"

const int READ = 0;  // Variable de lectura para pipe
const int WRITE = 1; // Variable de escritura para pipe

/**
 * Ejecuta una serie de comandos, posiblemente encadenados mediante pipes.
 * Para cada comando, se crea un proceso hijo que ejecuta el comando,
 * redirigiendo la entrada y salida según sea necesario.
 *
 * @param comandos Array de cadenas que contiene los comandos a ejecutar. Cada comando se encuentra en una posición del array.
 * @param num_comandos Número total de comandos en el array `comandos`.
 * @param favoritos Estructura que gestiona los comandos favoritos. Se usa para registrar ciertos comandos.
 */
void ejecutarComandos(char **comandos, int num_comandos, favs *favoritos)
{
    // si fueran tres comandos separados por dos pipes, entonces el arreglo seria [4], es decir,
    // num_comandos - 1 = 2 y eso multiplicado por 2 es 4.
    int mispipes[2 * (num_comandos - 1)], i;
    pid_t pid;

    // Este arreglo la unica utilidad que tiene es que el padre pueda ejecuar agregarComando (ciclo for linea 92)
    //  y hacerlo fuera del ciclo for linea 30
    //  Resulta que los hijos no funciona agregarComando (no se guardan en el txt)
    char ***args_array = malloc(num_comandos * sizeof(char **));

    // Crear pipes
    for (i = 0; i < num_comandos - 1; i++)
    {
        if (pipe(mispipes + i * 2) < 0)
        {
            perror("Error creando pipe.\n");
            exit(1);
        }
        // se crea el pipe
    }

    // Ejecutar los comandos
    for (i = 0; i < num_comandos; i++)
    {
        char **args = tokenEspacios(comandos[i]); // Obtener los argumentos del comando.
        args_array[i] = args;                     // Guardar args en el arreglo para su uso posterior en el padre

        if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL || strcmp(args[1], "~") == 0)
            {
                chdir(getenv("HOME"));
                agregarComando(favoritos, args); // Registrar el comando en favoritos
            }
            else
            {
                if (chdir(args[1]) != 0)
                {
                    perror("Error cambiando el directorio");
                }
            }
        }
        else if (strcmp(args[0], "set") == 0 && strcmp(args[1], "alarma") == 0)
        {
            if (fork() == 0)
            {
                manejoAlarma(args);
                agregarComando(favoritos, args); // Registrar el comando en favoritos
                exit(0);
            }
        }
        else if (strcmp(args[0], "favs") == 0)
        {
            elegirFavs(favoritos, args);
        }
        else
        {
            pid = fork();
            if (pid == 0)
            {
                // Redireccionar la entrada del proceso.
                if (i > 0)
                { // Solo si no es el primer comando
                    if (dup2(mispipes[(i - 1) * 2], READ) < 0)
                    { // dup2 retorna -1 si hay error
                        perror("Error duplicando descriptor de archivo (fd) para entrada.\n");
                        exit(1);
                    }
                    // Se duplica el descriptor de archivo para la entrada.
                }
                // Redireccionar la salida del proceso.
                if (i < num_comandos - 1)
                {
                    if (dup2(mispipes[i * 2 + 1], WRITE) < 0)
                    {
                        perror("Error duplicando descriptor de archivo (fd) para salida.\n");
                        exit(1);
                    }
                    // Se duplica el descriptor de archivo para la salida.
                }

                // Cerrar todos los pipes en el proceso hijo
                for (int j = 0; j < 2 * (num_comandos - 1); j++)
                {
                    close(mispipes[j]);
                }

                // Ejecutar el comando
                execvp(args[0], args);
                // Si execvp falla
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }
            else if (pid < 0)
            {
                perror("Error en fork()");
                exit(1);
            }
        }
    }

    // Cerrar todos los pipes en el proceso padre
    for (i = 0; i < 2 * (num_comandos - 1); i++)
    {
        close(mispipes[i]);
    }

    // Esperar a que todos los hijos terminen
    for (i = 0; i < num_comandos; i++)
    {
        wait(NULL);
        agregarComando(favoritos, args_array[i]); // Llamar agregarComando en el padre
        free(args_array[i]);                      // Liberar args después de que se use en el padre
    }

    // Liberar el arreglo de punteros a args
    free(args_array);
}
