#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

float A[2][2] = {2, 1, 5, 7};
float b[2] = {11, 13};
float x[2] = {1, 1};

pthread_barrier_t barrier;

void *Jacobi(void *threadid);


int main() {
    int n, rc;
    scanf("%d", &n);
    pthread_t threads[n];
    int *ids[n];
    pthread_barrier_init(&barrier, NULL, n); // Inicializa barreira para n threads

    for(int i = 0; i < n; i++) {
        ids[i] = (int *) malloc(sizeof(int));
        *ids[i] = i;
        rc = pthread_create(&threads[i], NULL, Jacobi, (void *) ids[i]);

        if(rc) {
            printf("Erro ao criar thread %d\n", i);
            exit(-1);
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
    int i = *((int *)threadid);

    // Metodo de Jacobi
    while(k < 10) {
        float sum = 0;
        for(int j = 0; j < 2; j++) {
            if(j != i) {
                sum += (A[i][j] * x[j]);
            }
        }
            
        pthread_barrier_wait(&barrier); // Espera todas as threads
        
        x[i] = ((b[i] - sum) / (A[i][i])); // x[i] no tempo k+1
        printf("No tempo %d, Thread %d calculou que x[%d] = %.4f\n", k+1, *((int *)threadid), i, x[i]);

        k++;
    }
}
