#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ***dividirComandosPorPipes(char **comandos, int *num_secciones) {
    int i = 0, j;

    // Contar cuántos delimitadores "|" hay
    *num_secciones = 1;
    while (comandos[i] != NULL) {
        if (strcmp(comandos[i], "|") == 0) {
            (*num_secciones)++;
        }
        i++;
    }

    // Reservar espacio para las secciones
    char ***secciones = (char ***)malloc(*num_secciones * sizeof(char **));

    // Dividir el arreglo en secciones
    i = 0;
    for (j = 0; j < *num_secciones; j++) {
        secciones[j] = &comandos[i];

        // Encontrar el final de la sección
        while (comandos[i] != NULL && strcmp(comandos[i], "|") != 0) {
            i++;
        }

        // Terminar la sección actual con NULL
        if (comandos[i] != NULL) {
            comandos[i] = NULL; // Terminar la sección con NULL
            i++;
        }
    }

    return secciones; // Retornar el arreglo de arreglos
}

void imprimirSecciones(char ***secciones, int num_secciones) {
    for (int j = 0; j < num_secciones; j++) {
        printf("Sección %d:\n", j + 1);
        int i = 0;
        while (secciones[j][i] != NULL) {
            printf("comandos[%d]: %s\n", i, secciones[j][i]);
            i++;
        }
        printf("\n");
    }
}

int main() {
    // Ejemplo de arreglo de comandos
    char *comandos[] = {"ls", "-l", NULL};
    int num_secciones;

    // Dividir el arreglo por los delimitadores "|"
    char ***secciones = dividirComandosPorPipes(comandos, &num_secciones);

    // Imprimir las secciones
    imprimirSecciones(secciones, num_secciones);

    // Liberar memoria
    free(secciones);

    return 0;
}
