#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5

void *PrintHello(void *threadid) {
    long tid = *((long *) threadid);
    printf("Hello, World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}


int main(void) {
    pthread_t threads[NUM_THREADS];
    long *taskids[NUM_THREADS];

    int rc, t;

    for(t = 0; t < NUM_THREADS; t++) {
        taskids[t] = (long *) malloc(sizeof(long));
        *taskids[t] = t;
        printf("In main: creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);
        if(rc) {
            printf("ERRO; código de retorno é %d\n", rc);
            exit(-1);
        } 
    }

    pthread_exit(NULL);
    // Desalocar as posicoes de taskids
}
