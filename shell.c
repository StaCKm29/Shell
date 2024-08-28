
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


int main() {
    char input[1024];  // Buffer para almacenar la entrada del usuario
    char *comandos[1024];

    while (1) {
        printf("Usuario 👾 ");  // Imprimir un prompt
        fgets(input, sizeof(input), stdin);  // Leer la entrada del usuario

        // Eliminar el salto de línea final que fgets incluye
        input[strcspn(input, "\n")] = 0;

        // Si el usuario ingresa "exit", salir del programa
        if (strcmp(input, "exit") == 0) {
            break;
        }

        if (strlen(input) == 0) {
            continue;
        }

        pid_t pid;
        pid = fork();
        if (pid == 0) {  // Proceso hijo
            extraerComandos(input, comandos);
            execvp(comandos[0], comandos);
            perror("Error ejecutando el comando");
            exit(1);
        } else if (pid > 0) {  // Proceso padre
            wait(NULL);
        } else {  // Error en fork
            perror("Fork falló");
            exit(1);
        }
    }

    return 0;
}
