#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *PrintHello(void *threadid) {
    printf("Hello, World!\n");
    pthread_exit(NULL);
}


int main(void) {
    pthread_t thread;
    int rc;
    rc = pthread_create(&thread, NULL, PrintHello, NULL);
    if(rc) {
        printf("ERRO; código de retorno é %d\n", rc);
        exit(-1);
    }
    pthread_exit(NULL);
}
