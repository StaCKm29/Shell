#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "favs.h"
#include "tokenPipes.h"
#include "ejecutarComandos.h"

//Compilar con gcc main.c tokenPipes.c ejecutarComandos.c tokenEspacios.c alarma.c favs.c -o shell
// ./shell

int main() {
    favs favoritos; //Estructura para almacenar los comandos favoritos
    iniciarFavs(&favoritos);

    char input[1024];   // Buffer para almacenar la entrada del usuario
    char **comandos;    // Array para almacenar los comandos separados por pipes
    int num_comandos;   // Número de comandos separados por pipes

    while (1) {
        printf("\033[1;37mOhMyShell 👾 \033[0m"); // Imprimir un prompt
        fgets(input, sizeof(input), stdin);     // Leer la entrada del usuario
        input[strcspn(input, "\n")] = 0; // Eliminar el salto de línea final que fgets incluye

        // Asignar memoria para los comandos en cada iteración
        comandos = malloc(1024 * sizeof(char *));

        // Dividir la entrada por pipes
        tokenPipes(input, &comandos, &num_comandos);

        // Permitir salir del bucle con el comando exit.
        if (strcmp(comandos[0], "exit") == 0) {
            crearArchivo(&favoritos, "");
            free(comandos);  // Liberar memoria antes de salir
            exit(0);  // Asegurar que el programa completo termine
        }

        // Ejecutar los otros comandos divididos por pipes
        ejecutarComandos(comandos, num_comandos, &favoritos);
    }
}
