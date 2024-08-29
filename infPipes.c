#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dividirPorPipes(char **comandos, char ****secciones, int *num_secciones) {
    int i = 0, j = 0;

    // Contar cuántos delimitadores "|" hay
    *num_secciones = 1;
    while (comandos[i] != NULL) {
        if (strcmp(comandos[i], "|") == 0) {
            (*num_secciones)++;
        }
        i++;
    }

    // Reservar espacio para las secciones
    *secciones = (char ***)malloc(*num_secciones * sizeof(char **));

    // Dividir el arreglo en secciones
    i = 0;
    for (j = 0; j < *num_secciones; j++) {
        // Encontrar el inicio de la sección
        (*secciones)[j] = &comandos[i];

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

    // Terminar la última sección con NULL
    //(*secciones)[*num_secciones - 1] = &comandos[i];
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
    char *comandos[] = {"ls", "-l", "|", "grep", ".c", "|", "wc","|", "mkdir","marcos", NULL};
    char ***secciones;
    int num_secciones;

    // Dividir el arreglo por los delimitadores "|"
    dividirPorPipes(comandos, &secciones, &num_secciones);

    // Imprimir las secciones
    imprimirSecciones(secciones, num_secciones);

    // Liberar memoria
    free(secciones);

    return 0;
}
