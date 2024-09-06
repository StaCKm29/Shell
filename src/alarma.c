#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

char *mensajeRecibido;

void sig_Alarma_Handler(int p){
	printf("%s \n", mensajeRecibido);
}

void setAlarma(int segundos, char *mensaje) {
	mensajeRecibido = mensaje;
	signal(SIGALRM, sig_Alarma_Handler);
    alarm(segundos);
    pause();
}

void manejoAlarma(char **args){
	if(args[2] == NULL || args[3] == NULL){
        printf("Error: Alguno de los argumentos es nulo.\n");
	}
	else{
		char *finalCadena;
		char *mensaje;
		mensaje = malloc(1024 * sizeof(char));
		strcpy(mensaje, args[3]);
		int indice = 4;
		while ( args[indice] != NULL){
			strcat(mensaje, " ");
			strcat(mensaje, args[indice]);
			indice++;
		}
		int segundos = strtol(args[2], &finalCadena, 10);
		if (*finalCadena != '\0' || segundos <= 0) {
			printf("Error: El argumento no es un número válido.\n");
			free(mensaje);
	    }else{
			setAlarma(segundos, mensaje);
	        free(mensaje);
	    }
    }
}
