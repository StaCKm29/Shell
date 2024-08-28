
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

void extraerComandos(char *input, char **comandos){
    char *token = strtok(input, " ");
    int i = 0;
    while(token != NULL){
        comandos[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    comandos[i] = NULL;
}

void imprimirArreglo(char **arreglo) {
    int i = 0;
    while (arreglo[i] != NULL) {
        printf("%s ,", arreglo[i]);
        i++;
    }
}


int main() {
    char input[1024];  // Buffer para almacenar la entrada del usuario.
    char *comandos[1024]; // Buffer para almacenar los comandos.


    while (1) {
        printf("\033[1;37mOhMyShell 👾 \033[0m");  // Imprimir un prompt
        fgets(input, sizeof(input), stdin);  // Leer la entrada del usuario
        // Eliminar el salto de línea final que fgets incluye
        input[strcspn(input, "\n")] = 0;

        // Si el usuario ingresa "exit", salir del programa
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Si el usuario presiona enter sin ingresar nada, continuar
        if (strlen(input) == 0) {
            continue;
        }

        extraerComandos(input, comandos);

        //El padre debe ejecutar el comando cd.
        if(strcmp(comandos[0], "cd") == 0){
            // Si no hay argumento para cd, cambiar al directorio home
            if (comandos[1] == NULL || strcmp(comandos[1], "~") == 0) {
                chdir(getenv("HOME"));
            } else {
                if (chdir(comandos[1]) != 0) {
                    perror("Error cambiando el directorio");
                }
            }
        }else {
            if (fork() == 0) { // Proceso hijo
                execvp(comandos[0], comandos);
                perror("Error ejecutando el comando");
                exit(1);
            } else {
                wait(NULL);
            }
        }
    }

    return 0;
}
