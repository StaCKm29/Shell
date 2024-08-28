
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/*
void sig_handler(int signo)
{
    if (signo == SIGINT)
        printf("Recibí SIGINT\n");
}*/

void extraerComandos(char *input, char ***comandos, int *tamaño_buf){
    int i = 0;
    char *token = strtok(input, " ");

    *comandos = malloc((*tamaño_buf) * sizeof(char *));
    if (!comandos){
        printf("Error en memoria");
        exit(1);
    }

    while (token != NULL)
    {
        (*comandos)[i] = token;
        i++;

        if (i >= *tamaño_buf)
        {
            *tamaño_buf += 64;
            *comandos = realloc(*comandos, (*tamaño_buf) * sizeof(char *));
            if (!*comandos)
            {
                printf("Error en redimensionar memoria");
                exit(1);
            }
        }
        token = strtok(NULL, " ");
    }
    (*comandos)[i] = NULL;
}

int main()
{
    char input[1024]; // Buffer para almacenar la entrada del usuario
    char **comandos = NULL;
    int tamaño_buf = 64;

    while (1){
        printf("\033[1;37mOhMyShell 👾: \033[0m");              // Imprimir un prompt
        fgets(input, sizeof(input), stdin); // Leer la entrada del usuario

        // Eliminar el salto de línea final que fgets incluye
        input[strcspn(input, "\n")] = 0;

        // Si el usuario ingresa "exit", salir del programa
        if (strcmp(input, "exit") == 0)
        {
            break;
        }

        if (strlen(input) == 0){
            continue;
        }

        extraerComandos(input, &comandos, &tamaño_buf);
        // Si el primer comando es "cd", cambiar el directorio
        if (strcmp(comandos[0], "cd") == 0) {
            // Si no hay argumento para cd, cambiar al directorio home
            if (comandos[1] == NULL || strcmp(comandos[1], "~") == 0)
                chdir(getenv("HOME"));
        } else {
            if(fork() == 0) {
                execvp(comandos[0], comandos);
                perror("Error ejecutando el comando");
                exit(1);
            } else {
                wait(NULL);
            }
        }
        free(comandos);
        comandos = NULL;

    }

    return 0;
}