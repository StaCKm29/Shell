#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

char *mensajeRecibido;

/**
 * Manejador de la señal SIGALRM que imprime el mensaje almacenado.
 *
 * @param p Número de señal (sin uso en la función, se evita la advertencia con (void)p).
 */
void sig_Alarma_Handler(int p){
    (void)p;
    printf("%s \n", mensajeRecibido);
}

/**
 * Configura una alarma que se activará después de un número determinado de segundos,
 * mostrando un mensaje cuando se dispare la señal SIGALRM.
 *
 * @param segundos Tiempo en segundos hasta que la alarma se dispare.
 * @param mensaje Mensaje que será impreso cuando la alarma se dispare.
 */
void setAlarma(int segundos, char *mensaje) {
    mensajeRecibido = mensaje;
    signal(SIGALRM, sig_Alarma_Handler);  // Configura el manejador para SIGALRM
    alarm(segundos);  // Programa la alarma para que se dispare después de "segundos"
    pause();  // Pausa la ejecución del programa hasta que la señal sea recibida
}

/**
 * Maneja la creación de la alarma a partir de los argumentos proporcionados.
 * Valida los argumentos y extrae el mensaje y los segundos para configurar la alarma.
 *
 * @param args Array de cadenas que contiene los argumentos, donde:
 *        - args[2]: Es el número de segundos (debe ser un entero positivo).
 *        - args[3] en adelante: Es el mensaje que se mostrará al activarse la alarma.
 */
void manejoAlarma(char **args){
    if (args[2] == NULL || args[3] == NULL) {
        printf("Error: Alguno de los argumentos es nulo.\n");
    }
    else {
        char *finalCadena;
        char *mensaje;
        mensaje = malloc(1024 * sizeof(char));  // Reserva memoria para el mensaje
        strcpy(mensaje, args[3]);  // Copia el primer segmento del mensaje

        int indice = 4;
        while (args[indice] != NULL) {
            strcat(mensaje, " ");  // Añade espacios entre palabras
            strcat(mensaje, args[indice]);  // Añade las siguientes palabras al mensaje
            indice++;
        }

        int segundos = strtol(args[2], &finalCadena, 10);  // Convierte args[2] a entero
        if (*finalCadena != '\0' || segundos <= 0) {
            printf("Error: El argumento no es un número válido.\n");
            free(mensaje);  // Libera la memoria asignada si hay un error
        } else {
            setAlarma(segundos, mensaje);  // Configura la alarma si los argumentos son válidos
            free(mensaje);  // Libera la memoria después de usar el mensaje
        }
    }
}
