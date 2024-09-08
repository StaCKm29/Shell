#ifndef ALARMA_H
#define ALARMA_H

void sig_Alarma_Handler(int p);
void setAlarma(int segundos, char *mensaje);
void manejoAlarma(char **args);

#endif