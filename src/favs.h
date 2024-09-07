#ifndef FAVS_H
#define FAVS_H

// Declaración del struct
typedef struct
{
    char ***comandos; // Almacenamiento de comandos en memoria
    int tamaño;       // Tamaño actual
    int capacidad;    // Tamaño maximo, se actualizara mediante realloc
    char ruta_archivo[1024];
} favs;

void iniciarFavs(favs *favs);
void crearArchivo(favs *favs, char *ruta);
void crearRutaDeArchivoAlSalir(char *ruta, char *ruta_a_guardar);
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

#endif
