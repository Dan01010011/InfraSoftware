#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int numThreads = 0; // Numero de threads esperando na lista de execucao
const int n = 2;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t lista_pronto;
pthread_cond_t vazia;

void *thread_code(void *threadid);
void *select(void *threadid);


int main() {
    int n;
    //scanf("%d", &n);
    pthread_t threads[n];
    pthread_t escalonador;
    int *ids[n];

    for(int i = 0; i < n; i++) {
        ids[i] = (int *) malloc(sizeof(int));
        *ids[i] = i;
        pthread_create(&threads, NULL, thread_code, (void *) ids[i]);
    }
    
    pthread_create(&escalonador, NULL, , NULL);

    pthread_exit(NULL);
}


void *thread_code(void *threadid) {
    pthread_mutex_lock(&mutex);

    while(numThreads == n) {    
        pthread_cond_wait(&lista_pronto, &mutex);
    }

    numThreads++;

    if(numThreads == 1) {
        pthread_cond_signal(&vazia);
    }

    pthread_mutex_unlock(&mutex);
}
