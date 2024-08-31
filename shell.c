
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

char **extraerComandos(char *input)
{
    int i = 0, tamaño_buf = 64;
    char *token = strtok(input, " ");

    char **comandos = malloc(tamaño_buf * sizeof(char *));
    if (!comandos)
    {
        printf("Error en memoria");
        exit(1);
    }

    while (token != NULL)
    {
        comandos[i] = token;
        i++;

        if (i >= tamaño_buf)
        {
            tamaño_buf += 64;
            comandos = realloc(comandos, tamaño_buf * sizeof(char *));
            if (!comandos)
            {
                printf("Error en redimensionar memoria");
                exit(1);
            }
        }
        token = strtok(NULL, " ");
    }
    comandos[i] = NULL;
    return comandos;
}

int main()
{
    int tamaño_buf = 1024;
    int tamaño_actual = tamaño_buf;

    char *input = malloc(tamaño_buf * sizeof(char));
    if (!input)
    {
        printf("Error en memoria");
        exit(1);
    }

    int l = 0, c;

    while (1)
    {
        printf("\033[1;37mOhMyShell 👾 \033[0m"); // Imprimir un prompt

        l = 0;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
            input[l++] = (char)c;
            if (l == tamaño_actual)
            {
                tamaño_actual += tamaño_buf;
                char *temp = realloc(input, tamaño_actual * sizeof(char));
                if (!temp)
                {
                    printf("Error en memoria");
                    free(input);
                    exit(1);
                }
                input = temp;
            }
        }

        // Si el usuario ingresa "exit", salir del programa
        if (strcmp(input, "exit") == 0)
        {
            break;
        }

        // Si el usuario presiona enter sin ingresar nada, continuar
        if (strlen(input) == 0)
        {
            continue;
        }

        char **comandos = extraerComandos(input);

        // El padre debe ejecutar el comando cd.
        if (strcmp(comandos[0], "cd") == 0)
        {
            // Si no hay argumento para cd, cambiar al directorio home
            if (comandos[1] == NULL || strcmp(comandos[1], "~") == 0)
            {
                chdir(getenv("HOME"));
            }
            else
            {
                if (chdir(comandos[1]) != 0)
                {
                    perror("Error cambiando el directorio");
                }
            }
            free(comandos);
        }
        else
        {
            if (fork() == 0)
            { // Proceso hijo
                execvp(comandos[0], comandos);
                free(comandos);
                perror("Error ejecutando el comando");
                exit(1);
            }
            else
            {
                wait(NULL);
                free(comandos);
            }
        }
    }

    return 0;
}