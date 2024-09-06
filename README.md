# Proyecto OhMyShell

### Instrucciones de uso:
Para compilar y ejecutar el proyecto se debe ingresar el siguiente comando en la terminal (estando en la carpeta src):

```sh
gcc main.c ejecutarComandos.c tokenEspacios.c tokenPipes.c alarma.c -o shell
./shell
```
La shell soporta el uso de varios comandos (incluyendo el uso de pipes), entro los cuales se encuentran:
- ls: Lista los archivos y directorios del directorio actual.
- cd [directorio]: Cambia el directorio actual al especificado.
- cd ..: Cambia el directorio actual al directorio padre.
- set alarma [segundos] [mensaje]: Configura una alarma que desplegará un mensaje luego de los segundos especificados. Todo lo que venga después del 
tiempo en segundos será considerado como mensaje.

### Funcionalidades:
- Comando cd para la navegación entre directorios.          

