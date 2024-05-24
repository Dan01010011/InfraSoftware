#define _XOPEN_SOURCE 600
#define n 2
#define I 3
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

float A[2][2] = {2, 1, 5, 7};
float b[2] = {11, 13};
float x[I] = {1, 1};
int iterator = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

void *Jacobi(void *threadid);


int main() {
    //int n;
    //scanf("%d", &n);
    pthread_t threads[n];
    int *ids[n], rc;
    pthread_barrier_init(&barrier, NULL, n); // Inicializa barreira para n threads

    for(int i = 0; i < n; i++) {
        ids[i] = (int *) malloc(sizeof(int));
        *ids[i] = i;
        rc = pthread_create(&threads[i], NULL, Jacobi, (void *) ids[i]);

        if(rc) {
            printf("Erro ao criar a thread %d\n", i);
            exit(1);
        }
    }
    for(int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier); // Destroi a barreira

    pthread_exit(NULL);
}


void *Jacobi(void *threadid) {
    int k = 0;
    int id = *((int *)threadid);

    while(k < 10) {
        float aux[I];
        for(int i = 0; i < I; i++) {
            aux[i] = x[i];
        }
        
        iterator = 0;
        pthread_barrier_wait(&barrier); // Espera todas as threads

        while(iterator < I) {
            pthread_mutex_lock(&mutex);
            iterator++;
            pthread_mutex_unlock(&mutex);
        
            // Metodo de Jacobi
            float sum = 0;
            for(int j = 0; j < I; j++) {
                if(j != iterator-1) {
                    sum += (A[iterator-1][j] * aux[j]);
                }
            }
                
            x[iterator-1] = ((b[iterator-1] - sum) / (A[iterator-1][iterator-1])); // x[i] no tempo k+1
            printf("No tempo %d, Thread %d calculou que x[%d] = %.4f\n", k+1, *((int *)threadid), iterator-1, x[iterator-1]);
        }

        pthread_barrier_wait(&barrier); // Espera todas as threads        

        k++;
    }
}
