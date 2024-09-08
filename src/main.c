#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "favs.h"
#include "tokenPipes.h"
#include "ejecutarComandos.h"

/**
 * Función principal del shell.
 * Lee la entrada del usuario, divide los comandos por pipes y los ejecuta.
 *
 * @authors : Jesús Guevara, Gabriel Castillo, Rodrigo Bascuñan, Marcos Martínez Rojas
 */

int main()
{
    favs favoritos; // Estructura para almacenar los comandos favoritos
    iniciarFavs(&favoritos);

    char input[1024]; // Buffer para almacenar la entrada del usuario
    char **comandos;  // Array para almacenar los comandos separados por pipes
    int num_comandos; // Número de comandos separados por pipes
    char ruta[256];

    while (1)
    {
        if (getcwd(ruta, sizeof(ruta)) == NULL)
        {
            printf("Error en obtener la ruta\n");
            break;
        }

        printf("\033[1;34mOhMyShell:\033[0m \033[1;37m~%s\033[0m 👾 ", ruta); // Imprimir un prompt
        fgets(input, sizeof(input), stdin);                 // Leer la entrada del usuario
        input[strcspn(input, "\n")] = 0;                    // Eliminar el salto de línea final que fgets incluye

        // Asignar memoria para los comandos en cada iteración
        comandos = malloc(1024 * sizeof(char *));

        // Dividir la entrada por pipes
        tokenPipes(input, &comandos, &num_comandos);

        // Permitir salir del bucle con el comando exit.
        if (strcmp(comandos[0], "exit") == 0)
        {
            if (strcmp(favoritos.ruta_archivo, "") != 0)
            {
                char ruta_estandar[1024];
                char *nombreArchivo = "/ruta.txt";
                char *rutaHome = getenv("HOME");
                snprintf(ruta_estandar, sizeof(ruta_estandar), "%s%s", rutaHome, nombreArchivo);
                guardarComandos(&favoritos);
                crearRutaDeArchivoAlSalir(ruta_estandar, favoritos.ruta_archivo);
            }
            free(comandos); // Liberar memoria antes de salir
            exit(0);        // Asegurar que el programa completo termine
        }

        // Ejecutar los otros comandos divididos por pipes
        ejecutarComandos(comandos, num_comandos, &favoritos);
    }
}
