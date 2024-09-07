#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

typedef struct
{
    char ***comandos; // Almacenamiento de comandos en memoria
    int tamaño;       // Tamaño actual
    int capacidad;    // Tamaño maximo, se actualizara mediante realloc
    char ruta_archivo[1024];
} favs;

char **extraerComandos(char *input, int index);
void iniciarFavs(favs *favs);
void crearArchivo(favs *favs, char *ruta);
void agregarComando(favs *favs, char **comando);
void mostrarComandos(char *ruta);
void mostrarComandosPrintf(favs *favs);
void eliminarComando(favs *favs, int num1, int num2);
void borrarComandos(char *ruta);
void buscarComandos(favs *favs, const char *sstring);
void ejecutarComando(favs *favs, int num);
void cargarComando(favs *favs);
int verificarComandoEjecutable(char **comando);
void freeFavs(favs *favs);
void guardarComandos(favs *favs);
void elegirFavs(favs *favs, char **comando);
int esNumerico(char *str);
int contador_caracteres(char *linea, char limite);

char **extraerComandos(char *input, int index)
{
    int i = index, tamaño_buf = 64;
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

// Inicializo la estructura de datos
void iniciarFavs(favs *favs)
{
    favs->comandos = malloc(10 * sizeof(char **));
    favs->tamaño = 0;
    favs->capacidad = 10;
    strcpy(favs->ruta_archivo, "");
}
// Creacion del archivo txt
void crearArchivo(favs *favs, char *ruta)
{
    FILE *archivo = fopen(ruta, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    strcpy(favs->ruta_archivo, ruta);

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
    printf("Archivo creado\n");
}
// Crea el archivo ruta txt en direccion HOME
void crearRutaDeArchivoAlSalir(char *ruta, char *ruta_a_guardar)
{
    FILE *archivo = fopen(ruta, "w");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo\n");
        return;
    }

    fprintf(archivo, "%s\n", ruta_a_guardar);
    fclose(archivo);
}
// Agregar un comando a la lista de favoritos (Recordar no agregar los comandos relacionados con favs)
void agregarComando(favs *favs, char **comando)
{

    if (verificarComandoEjecutable(comando))
    {
        return;
    }

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
    printf("Mostrando comandos: \n");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
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
                printf("Comando %d: %s ", i + 1, favs->comandos[i][j]);
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
// Ejecuta los comandos del txt
void ejecutarComando(favs *favs, int num)
{
    if (num < 1 || num > favs->tamaño)
    {
        printf("Número de comando inválido.\n");
        return;
    }

    // Solo tomar el comando principal
    char *comando = favs->comandos[num - 1][0];
    char *args[] = {comando, NULL};

    if (strcmp(comando, "cd") == 0)
    {
        if (favs->comandos[num - 1][1] == NULL || strcmp(favs->comandos[num - 1][1], "~") == 0)
        {
            chdir(getenv("HOME"));
            return;
        }
        else
        {
            if (chdir(favs->comandos[num - 1][1]) != 0)
            {
                perror("Error cambiando el directorio");
            }
        }
    }

    pid_t pid = fork();
    if (pid == 0)
    { // Proceso hijo
        execvp(args[0], args);
        perror("Error al ejecutar el comando");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL); // Esperar a que el hijo termine
    }
    else
    {
        perror("Error creando el proceso");
    }
}

// Devuelve la ruta del archivo txt en ruta estandar
char *leerRutaDeArchivo(char *ruta)
{
    FILE *archivo;
    static char rutaGuardada[1024]; // Variable para almacenar la ruta leída

    archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo\n");
        return NULL;
    }

    // Leer la primera línea del archivo
    if (fgets(rutaGuardada, sizeof(rutaGuardada), archivo) != NULL)
    {
        // Eliminar el salto de línea al final si existe
        rutaGuardada[strcspn(rutaGuardada, "\n")] = '\0';
    }
    else
    {
        printf("Error al leer la ruta desde el archivo.\n");
        fclose(archivo);
        return NULL;
    }

    fclose(archivo);
    return rutaGuardada;
}

// Despliega los comandos del archivo y los devuelve a la memoria
void cargarComando(favs *favs)
{
    // Ruta por defecto
    char ruta_estandar[1024];
    char *nombreArchivo = "/ruta.txt";
    char *rutaHome = getenv("HOME");
    snprintf(ruta_estandar, sizeof(ruta_estandar), "%s%s", rutaHome, nombreArchivo);

    // Leer la ruta del archivo desde el archivo de configuración
    char *ruta = leerRutaDeArchivo(ruta_estandar);
    if (ruta == NULL)
    {
        printf("Error: No se pudo leer la ruta del archivo de comandos.\n");
        return;
    }

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        printf("Error: No se pudo abrir el archivo de comandos: %s\n", ruta);
        return;
    }

    char linea[1024];
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        // Eliminar el salto de línea al final, si lo tiene
        linea[strcspn(linea, "\n")] = 0;

        // Extraer el índice (número de comando) y el comando
        char *comando_str = strchr(linea, '-') + 1; // Buscar el delimitador '-' y avanzar

        if (comando_str != NULL)
        {
            char **comando = extraerComandos(comando_str, 0);

            // Verificar si se extrajo un comando válido
            if (comando[0] != NULL)
            {
                // Agregar el comando a la estructura favs
                agregarComando(favs, comando);
            }
        }
    }

    // Copiar la ruta del archivo a la estructura favs
    strcpy(favs->ruta_archivo, ruta);
    fclose(archivo);

    printf("Comandos cargados correctamente desde %s\n", ruta);
}

// Devuelve si un string contiene numeros
int esNumerico(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; // No es numérico
        }
    }
    return 1; // Es numérico
}
// Cuenta los caracteres hasta un limite
int contador_caracteres(char *linea, char limite)
{
    int index = 0;
    while (linea[index] != '\0' && linea[index] != limite)
    {
        index++;
    }
    return index;
}
// Verifica que un comando sea ejecutable
int verificarComandoEjecutable(char **comando)
{
    // Busca en el PATH si el comando es accesible
    if (access(comando[0], X_OK) == 0)
    {
        return 1; // El comando es accesible y ejecutable
    }
    else
    {
        return 0; // No es accesible o no es ejecutable
    }
}
// Libera la memoria
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
// Guarda los comandos en el archivo txt
void guardarComandos(favs *favs)
{
    // Abre el archivo en modo de escritura
    FILE *archivo = fopen(favs->ruta_archivo, "w");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo para guardar comandos");
        return;
    }

    // Recorre la lista de comandos y guarda cada uno en el archivo
    for (int i = 0; i < favs->tamaño; i++)
    {
        fprintf(archivo, "%d-", i + 1);
        for (int j = 0; favs->comandos[i][j] != NULL; j++)
        {
            fprintf(archivo, "%s ", favs->comandos[i][j]);
        }
        fprintf(archivo, "\n"); // Nueva línea para separar comandos
    }

    fclose(archivo);
    printf("Comandos guardados en %s\n", favs->ruta_archivo);
}

// funcion switch para elegir que funcion usar mediante el cmd
void elegirFavs(favs *favs, char **comando)
{
    if (comando[1] == NULL)
    {
        printf("No se reconoce el comando favs\n");
        return;
    }

    if (strcmp(comando[1], "crear") == 0)
    {
        if (comando[2] != NULL)
        {
            strcpy(favs->ruta_archivo, comando[2]);
            crearArchivo(favs, favs->ruta_archivo);
        }
        else
        {
            printf("Error: Se requiere una ruta de archivo para crear.\n");
        }
    }
    else if (strcmp(comando[1], "mostrar") == 0)
    {
        mostrarComandos(favs->ruta_archivo);
    }
    else if (strcmp(comando[1], "eliminar") == 0)
    {
        if (comando[2] != NULL)
        {
            int num1, num2;
            if (sscanf(comando[2], "%d,%d", &num1, &num2) == 2)
            {
                eliminarComando(favs, num1, num2);
            }
            else
            {
                printf("Error: Debes proporcionar dos números separados por coma.\n");
            }
        }
        else
        {
            printf("Error: Debes proporcionar los números de comandos a eliminar.\n");
        }
    }
    else if (strcmp(comando[1], "buscar") == 0)
    {
        if (comando[2] != NULL)
        {
            buscarComandos(favs, comando[2]);
        }
        else
        {
            printf("Error: Debes proporcionar un substring para buscar.\n");
        }
    }
    else if (strcmp(comando[1], "borrar") == 0)
    {
        borrarComandos(favs->ruta_archivo);
        favs->tamaño = 0; // Actualizar tamaño a 0 ya que se borran todos los comandos
    }
    else if (strcmp(comando[1], "cargar") == 0)
    {
        cargarComando(favs);
        mostrarComandosPrintf(favs); // Mostrar los comandos cargados en la memoria
    }
    else if (strcmp(comando[1], "guardar") == 0)
    {
        guardarComandos(favs);
    }
    else if (strcmp(comando[1], "terminal") == 0)
    { // ELIMINAR DESPUES
        mostrarComandosPrintf(favs);
    }
    else if (strcmp(comando[2], "ejecutar") == 0)
    {
        if (comando[2] != NULL)
        {
            int num = atoi(comando[1]);
            ejecutarComando(favs, num);
        }
        else
        {
            printf("Error: Debes proporcionar el número del comando a ejecutar.\n");
        }
    }

    else
    {
        printf("Error: Comando de favs no reconocido.\n");
    }
}

int main()
{
    favs misFavoritos;
    iniciarFavs(&misFavoritos);

    int tamaño_buf = 1024;
    int tamaño_actual = tamaño_buf;

    char *input = malloc(tamaño_buf * sizeof(char));
    if (!input)
    {
        printf("Error en memoria");
        exit(1);
    }

    int l = 0, c;
    char ruta[1024];

    while (1)
    {
        if (getcwd(ruta, sizeof(ruta)) == NULL)
        {
            printf("Error en cwd");
            free(input);
            exit(1);
        }

        printf("\033[1;37mOhMyShell 👾 %s \033[0m", ruta); // Imprimir un prompt

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
        input[l] = '\0';

        // Si el usuario ingresa "exit", salir del programa
        if (strcmp(input, "exit") == 0)
        {
            if (strcmp(misFavoritos.ruta_archivo, "") != 0)
            {
                char ruta_estandar[1024];
                char *nombreArchivo = "/ruta.txt";
                char *rutaHome = getenv("HOME");
                snprintf(ruta_estandar, sizeof(ruta_estandar), "%s%s", rutaHome, nombreArchivo);
                crearRutaDeArchivoAlSalir(ruta_estandar, misFavoritos.ruta_archivo);
            }
            break;
        }

        // Si el usuario presiona enter sin ingresar nada, continuar
        if (strlen(input) == 0)
        {
            continue;
        }

        char **comandos = extraerComandos(input, 0);

        // El padre debe ejecutar el comando cd.
        if (strcmp(comandos[0], "cd") == 0)
        {
            if (comandos[1] == NULL || strcmp(comandos[1], "~") == 0)
            {
                char *args[] = {"cd", NULL};
                agregarComando(&misFavoritos, args);
                chdir(getenv("HOME"));
            }
            else
            {
                if (chdir(comandos[1]) != 0)
                {
                    perror("Error cambiando el directorio");
                }
            }
            char *args[] = {"cd", NULL};
            agregarComando(&misFavoritos, args);
        }
        else if (strcmp(comandos[0], "favs") == 0)
        {
            elegirFavs(&misFavoritos, comandos);
        }
        else
        {
            if (fork() == 0)
            { // Proceso hijo
                execvp(comandos[0], comandos);
                perror("Error ejecutando el comando");
                exit(1);
            }
            else
            {
                wait(NULL);
                agregarComando(&misFavoritos, comandos);
            }
        }

        free(comandos);
    }

    // Liberar memoria y salir
    freeFavs(&misFavoritos);
    free(input);
    return 0;
}