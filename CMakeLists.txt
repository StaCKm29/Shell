cmake_minimum_required(VERSION 3.29)
project(src/shell C)

set(CMAKE_C_STANDARD 11)

add_executable(shell src/main.c src/shell.c src/infPipes.c
        src/tokenespacios.c
        src/infPipes.c
        src/infPipes.c
        src/tokenespacios.c)

