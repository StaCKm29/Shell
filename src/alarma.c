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
