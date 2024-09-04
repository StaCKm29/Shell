
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct
{
    char ***comandos; // Almacenamiento de comandos en memoria
    int tamaño;       // Tamaño actual
    int capacidad;    // Tamaño maximo, se actualizara mediante realloc
    char ruta_archivo[1024];
} favs;

// Inicializo la estructura de datos
void iniciarFavs(favs *favs)
{
    favs->comandos = malloc(10 * sizeof(char **));
    favs->tamaño = 0;
    favs->capacidad = 10;
    favs->ruta_archivo[0] = '\0';
}
// Creacion del archivo txt
void crearArchivo(favs *favs, char *ruta)
{
    FILE *archivo = fopen(ruta, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo");
        return;
    }

    // Recorrer los comandos y guardarlos en el archivo
    for (int i = 0; i < favs->tamaño; i++)
    {
        fprintf(archivo, "%d-", i + 1);
        for (int j = 0; favs->comandos[i][j] != NULL; j++)
        {
            fprintf(archivo, "%s ", favs->comandos[i][j]); // Escribir cada comando y sus argumentos
        }
        fprintf(archivo, "\n"); // Nueva línea para separar comandos
    }
    fclose(archivo);
    printf("comandos guardados\n");
}

// Agregar un comando a la lista de favoritos (Recordar no agregar los comandos relacionados con favs)
void agregarComando(favs *favs, char **comando)
{
    // Aseguro que no se agregue comando favs,
    if (strcmp(comando[0], "favs") == 0)
    {
        return;
    }

    // Verifico si ya existe el comando
    for (int i = 0; i < favs->tamaño; i++)
    {
        if (strcmp(favs->comandos[i][0], comando[0]) == 0)
        {
            // Comando encontrado, ahora verificar argumentos
            int j, l;
            int nuevo_arg = 0;

            // Verificar cada argumento de "comando" con los argumentos ya existentes en favs->comandos[i]
            for (l = 1; comando[l] != NULL; l++)
            {
                int encontrado = 0;
                for (j = 1; favs->comandos[i][j] != NULL; j++)
                {
                    if (strcmp(comando[l], favs->comandos[i][j]) == 0)
                    {
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado)
                {
                    nuevo_arg++;
                }
            }

            // Si hay nuevos argumentos que agregar
            if (nuevo_arg > 0)
            {
                char **temp = realloc(favs->comandos[i], (j + nuevo_arg + 1) * sizeof(char *));
                if (!temp)
                {
                    printf("Error en reasignar memoria favs");
                    exit(1);
                }
                favs->comandos[i] = temp;

                // Agregar los nuevos argumentos
                for (l = 1; comando[l] != NULL; l++)
                {
                    int encontrado = 0;
                    for (j = 1; favs->comandos[i][j] != NULL; j++)
                    {
                        if (strcmp(comando[l], favs->comandos[i][j]) == 0)
                        {
                            encontrado = 1;
                            break;
                        }
                    }
                    if (!encontrado)
                    {
                        favs->comandos[i][j] = strdup(comando[l]);
                        favs->comandos[i][j + 1] = NULL; // Terminar con NULL
                    }
                }
            }
            return; // Comando ya existente fue actualizado, salir de la función
        }
    }

    // Reajuste de tamaño comandos
    if (favs->tamaño == favs->capacidad)
    {
        favs->capacidad *= 2;
        char ***temp = realloc(favs->comandos, favs->capacidad * sizeof(char **));
        if (!temp)
        {
            printf("Error en reasignar memoria");
            exit(1);
        }
        favs->comandos = temp;
    }

    // Copiar el comando y agregarlo
    int contador = 0;
    while (comando[contador] != NULL)
    {
        contador++;
    }

    // Asignar espacio en favs->comandos para el nuevo comando
    favs->comandos[favs->tamaño] = calloc(contador + 1, sizeof(char *)); // +1 para el NULL al final
    if (favs->comandos[favs->tamaño] == NULL)
    {
        printf("Error en asignar memoria para el nuevo comando");
        exit(1);
    }

    // Copiar los argumentos del comando
    for (int k = 0; k < contador; k++)
    {
        favs->comandos[favs->tamaño][k] = strdup(comando[k]); // Usamos strdup para duplicar la cadena
    }
    favs->comandos[favs->tamaño][contador] = NULL; // Añadir el NULL al final
    favs->tamaño += 1;
}

// Desplegar la lista de comandos existentes
void mostrarComandos(char *ruta)
{
    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo");
        return;
    }

    char linea[1024];
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        printf("%s", linea);
    }
    fclose(archivo);
}
// Desplegar comandos en cmd
void mostrarComandosPrintf(favs *favs)
{
    for (int i = 0; i < favs->tamaño; i++)
    {
        printf("Comando %d: ", i + 1);
        for (int j = 0; favs->comandos[i][j] != NULL; j++)
        {
            printf("%s ", favs->comandos[i][j]);
        }
        printf("\n");
    }
}
// Eliminar comandos entre los numeros dados
void eliminarComando(favs *favs, int num1, int num2)
{
    num1 -= 1;
    num2 -= 1;

    if (num1 < 0 || num2 >= favs->tamaño || num1 > num2)
    {
        printf("Error en el rango de valores\n");
        return;
    }

    // Liberar la memoria de los comandos que se eliminarán
    for (int i = num1; i <= num2; i++)
    {
        for (int j = 0; favs->comandos[i][j] != NULL; j++)
        {
            free(favs->comandos[i][j]); // Liberar cada cadena en el comando
        }
        free(favs->comandos[i]); // Liberar el array de cadenas
    }

    // Reorganizar los comandos restantes
    int desplazamiento = num2 - num1 + 1;
    for (int i = num1; i < favs->tamaño - desplazamiento; i++)
    {
        favs->comandos[i] = favs->comandos[i + desplazamiento];
    }

    // Ajustar el tamaño y limpiar los comandos restantes en la memoria
    favs->tamaño -= desplazamiento;
    for (int i = favs->tamaño; i < favs->capacidad; i++)
    {
        favs->comandos[i] = NULL;
    }
}
// Borrar toda la lista de comandos
void borrarComandos(char *ruta)
{
    FILE *archivo = fopen(ruta, "w");
    if (archivo == NULL)
    {
        printf("Error en abrir arhivo (borrarComando)");
        return;
    }

    fclose(archivo);
}
// Busqueda de comandos existentes
void buscarComandos(favs *favs, const char *sstring)
{
    int encontrados = 0;

    for (int i = 0; i < favs->tamaño; i++)
    {
        for (int j = 0; favs->comandos[i][j] != NULL; j++)
        {
            if (strstr(favs->comandos[i][j], sstring) != NULL)
            {
                printf("Comando #%d: %s ", i + 1, favs->comandos[i][j]);
                printf("\n");
                encontrados++;
                break; // Salir del bucle interno si ya encontramos una coincidencia
            }
        }
    }

    if (encontrados == 0)
    {
        printf("No se encontraron comandos que contengan '%s'.\n", sstring);
    }
}
// Uso de exec para comando elegido
void ejecutarComando()
{
}
// funcion switch para elegir que funcion usar mediante el cmd
void elegirFavs()
{
}

// Despliega los comandos del archivo y los devuelve a la memoria
void cargarComando(favs *favs, char *ruta)
{
    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        printf("Error en abrir el archivo");
        return;
    }

    char linea[1024];

    // Leer linea por linea
    while (fgets(linea, sizeof(linea), archivo))
    {
        // Eliminar salto de linea al final
        linea[strcspn(linea, "\n")] = 0;

        // Contar cantidad de argumentos
        int num_args = 0;
        char *temp = strdup(linea);
        char *token = strtok(temp, " ");
        while (token != NULL)
        {
            num_args++;
            token = strtok(NULL, " ");
        }
        free(temp);

        char **comando = malloc((num_args + 1) * sizeof(char *));
        int i = 0;
        token = strtok(linea, " ");
        while (token != NULL)
        {
            comando[i] = strdup(token);
            i++;
            token = strtok(NULL, " ");
        }
        comando[i] = NULL;

        agregarComando(favs, comando);
    }
    fclose(archivo);
    printf("comandos cargados correctamente en %s\n", ruta);
}

// Verifica si existe el comando
int verificarComando(const char *comando)
{
    char *path_env = getenv("PATH");
    if (path_env == NULL)
    {
        printf("No se pudo obtener la variable de entorno PATH\n");
        return 0;
    }

    char *path = strdup(path_env); // Copiar el PATH
    char *directorio = strtok(path, ":");

    while (directorio != NULL)
    {
        char ruta_comando[1024];
        snprintf(ruta_comando, sizeof(ruta_comando), "%s/%s", directorio, comando);

        if (access(ruta_comando, X_OK) == 0)
        {
            free(path);
            return 1; // Comando encontrado y ejecutable
        }

        directorio = strtok(NULL, ":");
    }

    free(path);
    return 0; // Comando no encontrado
}

void freeFavs(favs *favs)
{
    // Liberar cada comando
    for (int i = 0; i < favs->tamaño; i++)
    {
        char **comando = favs->comandos[i];
        for (int j = 0; comando[j] != NULL; j++)
        {
            free(comando[j]); // Liberar cada cadena
        }
        free(comando); // Liberar el array de cadenas
    }

    // Liberar la lista de comandos
    free(favs->comandos);
}

int main()
{
    favs misFavoritos;
    iniciarFavs(&misFavoritos);

    char *cmd1[] = {"ls", "-l", NULL};
    char *cmd2[] = {"ls", "-k", NULL};
    char *cmd3[] = {"ls", "-s", "pepe", NULL};
    char *cmd4[] = {"cd", "-l", NULL};
    char *cmd5[] = {"we", "-k", NULL};
    char *cmd6[] = {"xd", "-s", "pepe", NULL};
    char *cmd7[] = {"meme", "-l", NULL};
    char *cmd8[] = {"olui", "-k", NULL};
    char *cmd9[] = {"as", "-s", "pepe", NULL};
    char *cmd10[] = {"cx", "-l", NULL};
    char *cmd11[] = {"cat", "-k", NULL};
    char *cmd12[] = {"ls", "esquere", "asd", NULL};

    agregarComando(&misFavoritos, cmd1);
    agregarComando(&misFavoritos, cmd2);
    agregarComando(&misFavoritos, cmd3);
    agregarComando(&misFavoritos, cmd4);
    agregarComando(&misFavoritos, cmd5);
    agregarComando(&misFavoritos, cmd6);
    agregarComando(&misFavoritos, cmd7);
    agregarComando(&misFavoritos, cmd8);
    agregarComando(&misFavoritos, cmd9);
    agregarComando(&misFavoritos, cmd10);
    agregarComando(&misFavoritos, cmd11);
    agregarComando(&misFavoritos, cmd12);

    char ruta_archivo[1024] = "./comandos_favoritos.txt";

    crearArchivo(&misFavoritos, ruta_archivo);
    printf("Antes\n");
    mostrarComandos(ruta_archivo);

    eliminarComando(&misFavoritos, 1, 3);

    char ruta_archivo2[1024] = "./comandos_favoritoseliminados.txt";

    crearArchivo(&misFavoritos, ruta_archivo2);
    printf("\nDespues\n");
    mostrarComandos(ruta_archivo2);

    borrarComandos(ruta_archivo);
    printf("borrar todos los comandos:\n");
    mostrarComandos(ruta_archivo);

    printf("\nBuscando comandos que contengan 'xyz':\n");
    buscarComandos(&misFavoritos, "xyz");

    printf("\nBuscando comandos que contengan 'xd':\n");
    buscarComandos(&misFavoritos, "xd");

    // Cargar los comandos desde el archivo
    // cargarComando(&misFavoritos, ruta_archivo);

    // Mostrar comandos
    // mostrarComandos(ruta_archivo);

    // Liberar memoria (pendiente de implementar)
    freeFavs(&misFavoritos);

    // char comando[100];

    // printf("Ingrese un comando: ");
    // scanf("%s", comando);

    // if (verificarComando(comando))
    // {
    //     printf("El comando '%s' está correctamente escrito y es ejecutable.\n", comando);
    // }
    // else
    // {
    //     printf("El comando '%s' no está correctamente escrito o no es ejecutable.\n", comando);
    // }
    return 0;
}