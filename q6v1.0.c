#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define n 2
#define NUM_THREADS 30

int threads_exe = 0; // Numero de threads em execucao
int list = 0; // Numero de threads esperando na lista/fila de execução
int executadas = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t lista_pronto = PTHREAD_COND_INITIALIZER;
pthread_cond_t vazia = PTHREAD_COND_INITIALIZER;

void *thread_code(void *threadid);
void *escalonar();
void *agendar(void *threadid);
void *selecionar();


int main() {
    pthread_t threads[NUM_THREADS];
    pthread_t escalonador;
    int *ids[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) {
        ids[i] = (int *) malloc(sizeof(int));
        *ids[i] = i;
        pthread_create(&threads[i], NULL, thread_code, (void *) ids[i]);
    }
    
    pthread_create(&escalonador, NULL, escalonar, NULL);

    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); 
    }
    pthread_join(escalonador, NULL);

    pthread_exit(NULL);
}


void *thread_code(void *threadid) {
    list++;
    agendar(threadid);
    int i = 0;

    while(i < 10000) {
        i++;
    }

    threads_exe--;
    executadas++;
    printf("Thread %d terminou\n", *((int *) threadid));

    if(executadas == NUM_THREADS) {
        pthread_cond_signal(&vazia);
    }

    pthread_exit(NULL);
}

void *escalonar() {
    while(executadas != NUM_THREADS) {
        selecionar();
    }

    pthread_exit(NULL);
}

void *agendar(void *threadid) {
    pthread_mutex_lock(&mutex);

    while(threads_exe == n) {
        printf("Numero maximo de threads em execução atingindo\n");
        pthread_cond_wait(&lista_pronto, &mutex);
    }

    list--;
    threads_exe++;
    printf("Thread %d em execução\n", *((int *)threadid));
        
    if(list == 1) {
        pthread_cond_signal(&vazia);
    }

    pthread_mutex_unlock(&mutex);
}

void *selecionar() {
    pthread_mutex_lock(&mutex);

    while((list == 0) && (executadas != NUM_THREADS)) {
        printf("Escalonador dormindo\n");
        pthread_cond_wait(&vazia, &mutex);
    }

    pthread_cond_broadcast(&lista_pronto);
    
    pthread_mutex_unlock(&mutex);
}
