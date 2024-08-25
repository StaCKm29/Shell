
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void sig_handler(int signo)
{
    if (signo == SIGINT)
        printf("Recibí SIGINT\n");
}

int main(int argc, char *argv[]) {

    char *myargs[argc];
    int pid = fork();

    if (pid < 0) {//falla
        perror("Fork fallo,\n");
        exit(1);
    }

    if (pid == 0) { //hijo
        for (int i = 0; i<argc-1; i++) {
            myargs[i] = argv[i+1];
        }
        myargs[argc-1] = NULL;
        printf("$");
        execvp(myargs[0], myargs);
        perror("Error en execvp\n"); //falla
    } else { //padre
        wait(NULL);
        //printf("$");
    }
}


