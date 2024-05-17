#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define n 7

int numThreads = 0; // Numero de threads esperando na lista de execucao

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t lista_pronto = PTHREAD_COND_INITIALIZER;
pthread_cond_t vazia = PTHREAD_COND_INITIALIZER;

void *thread_code(void *threadid);
void *escalonar();
void *agendar(void *threadid);
void *selecionar();


int main() {
    pthread_t threads[n];
    pthread_t escalonador;
    int *ids[n];

    for(int i = 0; i < n; i++) {
        ids[i] = (int *) malloc(sizeof(int));
        *ids[i] = i;
        pthread_create(&threads[i], NULL, thread_code, (void *) ids[i]);
    }
    
    pthread_create(&escalonador, NULL, escalonar, NULL);

    for(int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL); 
    }
    pthread_join(escalonador, NULL);

    //pthread_exit(NULL);
}


void *thread_code(void *threadid) {
    for(int i = 0; i < n; i++) {
        agendar(threadid);
    }

    pthread_exit(NULL);
}

void *escalonar() {
    for(int i = 0; i < n; i++) {
        selecionar();
    }

    pthread_exit(NULL);
}

void *agendar(void *threadid) {
    pthread_mutex_lock(&mutex);

    while(numThreads == n) {    
        pthread_cond_wait(&lista_pronto, &mutex);
    }

    printf("Thread %d em execução\n", *((int *)threadid));
    numThreads++;

    if(numThreads == 1) {
        pthread_cond_signal(&vazia);
    }

    pthread_mutex_unlock(&mutex);
}

void *selecionar() {
    pthread_mutex_lock(&mutex);

    while(numThreads == 0) {
        pthread_cond_wait(&vazia, &mutex);
    }

    numThreads--;

    if(numThreads == n - 1) {
        pthread_cond_broadcast(&lista_pronto);
    }

    pthread_mutex_unlock(&mutex);
}
