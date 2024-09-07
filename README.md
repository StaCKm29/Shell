<h1 align="center">Proyecto OhMyShell</h1>
<h3 align="center">Sistemas Operativos</h3>

### Instrucciones de uso:
Para compilar y ejecutar el proyecto se debe ingresar el siguiente comando en la terminal (estando en la carpeta src):

```sh
gcc main.c ejecutarComandos.c tokenEspacios.c tokenPipes.c alarma.c -o shell
```
Una vez compilado, podemos ejecutar la shell con el siguiente comando:
```sh
./shell
```

Una vez aquí, aparecerá el promt de la shell
```sh
OhMyShell:~/home/lugar/del/directorio/Shell/cmake-build-debug 👾 
```
Por lo que estará lista y esperando para recibir comandos
### Comandos:

La shell soporta el uso de varios comandos, incluyendo los tipicos de una shell y comandos personalizados que fueron añadidos, implicando el uso de pipes(|) para conectar comandos
entre si.

Comandos añadidos usando chdir()
- `cd [directorio]`: Cambia el directorio actual al especificado.
- `cd ..`: Cambia el directorio actual al directorio padre.

Además, la shell puede ejecutar otros comandos externos mediante la función execvp(), tales como:
- `ls`: Lista los archivos y directorios del directorio actual.
-  `mv`: Mueve o renombra archivos y directorios.
-  `rm`: Elimina archivos o directorios.
-  `pwd`: Muestra el directorio de trabajo actual.
- `echo`: Imprime texto en la salida estándar.

También se pueden ejecutar comandos con argumentos adicionales y combinar la salida de estos usando pipes (|). Un ejemplo típico es:
```sh
ls | wc -l
```


### Recordatorio 
- `set alarma [segundos] [mensaje]:` Configura una alarma que desplegará un mensaje luego de los segundos especificados. Todo lo que venga después del 
tiempo en segundos será considerado como mensaje.

### Comandos `favs`(Gestión de Comandos Favoritos) :

`favs crear [ruta]` : Crea un archivo que contendrá los comandos que se irán guardando como favoritos
```sh
favs crear /ruta/hacia/archivo_favoritos.txt
```
`favs guardar` : Guarda una lista de comandos favoritos al directorio especificado

`favs mostrar` : Muestra todos los comandos favoritos guardados de forma enumerada. 
```sh
favs crear /ruta/hacia/archivo_favoritos.txt
```
`favs eliminar [num1,num2]` : Elimina el o los comandos favoritos guardados proporcionando el número
mostrado en favs mostrar
```sh
favs eliminar 1,2
```
Esto borraria los comandos 1 y 2 de la lista de comandos favoritos visto del favs mostrar

`favs buscar [substring]` : Busca comandos en la lista de favoritos que contengan la subcadena proporcionada en el argumento
```sh
favs buscar ls  
```
esto buscará y mostrará los comandos favortios que contengan ls

`favs cargar` : Carga la lista de comandos favoritos desde el archivo especificado en la ruta dada. Los comandos cargados estarán disponibles para ser utilizados en la sesión actual del shell.
```sh
favs cargar /ruta/hacia/archivo_favoritos.txt
```
`favs borrar` :  Borra todos los comandos favoritos almacenados en el archivo de comandos y vacía la lista de comandos en memoria.

<h3 align="left">Herramientas utilizadas: </h3>
<p align="left"> 
  <a href="https://www.cprogramming.com/" target="_blank" rel="noreferrer">
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="C programming" width="40" height="40"/> 
  </a> 
  <a href="https://valgrind.org/" target="_blank" rel="noreferrer"> 
    <img src="https://upload.wikimedia.org/wikipedia/en/thumb/f/f9/Valgrind_logo.png/200px-Valgrind_logo.png" alt="Valgrind" width="40" height="40"/> 
  </a> 
</p>
