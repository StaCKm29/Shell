#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern void tokenPipes(char *input, char ***comandos, int *num_comandos);
extern void ejecutarComandos(char **comandos, int num_comandos);

int main() {
    char input[1024];   // Buffer para almacenar la entrada del usuario
    char **comandos;    // Array para almacenar los comandos separados por pipes
    int num_comandos;   // Número de comandos separados por pipes

    while (1) {
        printf("\033[1;37mOhMyShell 👾 \033[0m"); // Imprimir un prompt
        fgets(input, sizeof(input), stdin);       // Leer la entrada del usuario

        // Eliminar el salto de línea final que fgets incluye
        input[strcspn(input, "\n")] = 0;

        // Permitir salir del bucle con un comando especial (por ejemplo, "exit")
        if (strcmp(input, "exit") == 0) {
            break;
        }
        // Asignar memoria para los comandos en cada iteración
        comandos = malloc(1024 * sizeof(char *));

        // Dividir la entrada por pipes
        tokenPipes(input, &comandos, &num_comandos);

        // Ejecutar los otros comandos divididos por pipes
        ejecutarComandos(comandos, num_comandos);
        }

    // Liberar la memoria después de usarla
    free(comandos);

    return 0;
}
