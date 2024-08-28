
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

int main() {
    char input[1024];  // Buffer para almacenar la entrada del usuario

    while(1) {
        printf("Usuario 👾");  // Imprimir un prompt
        fgets(input, sizeof(input), stdin);  // Leer la entrada del usuario

        // Eliminar el salto de línea final que fgets incluye
        input[strcspn(input, "\n")] = 0;

        if(strcmp(input, "exit") == 0) {
            exit(0);
        }
        //printf("Comando ingresado: %s\n", input);
    }

    return 0;
}


