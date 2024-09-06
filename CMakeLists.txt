cmake_minimum_required(VERSION 3.28.2)
project(src/shell C)

set(CMAKE_C_STANDARD 11)

add_executable(shell
        src/main.c
        src/tokenEspacios.c
        src/ejecutarComandos.c
        src/tokenPipes.c
        src/alarma.c
        src/favs.c
        src/tokenPipes.h
        src/alarma.h
        src/ejecutarComandos.h
)

