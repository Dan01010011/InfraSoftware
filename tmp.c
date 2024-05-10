#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_CLIENTS 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int *account[NUM_CLIENTS];

void *operations(void *threadid);


int main() {
    pthread_t threads[NUM_CLIENTS];
    int *ids[NUM_CLIENTS];
    int i;

    for(i = 0; i < NUM_CLIENTS; i++) {
        ids[i] = (int *) malloc(sizeof(int));
        account[i] = (int *) malloc(sizeof(int));
        *ids[i] = i;
        *account[i] = 1000;
        pthread_create(&threads[i], NULL, operations, (void *) ids[i]);
    }
    for(int i = 0; i < NUM_CLIENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
}


void *operations(void *threadid) {
    int operation;
    printf("Bem-vindo, Cliente %d. Qual operação deseja realizar?\n1. Saque\n2. Depósito\n3. Consultar Saldo\n.: ", *((int *) threadid));
    scanf("%d", &operation);
    pthread_mutex_lock(&mutex);

    switch(operation) {
        case 1: // Saque
            int saque;
            printf("Valor do saque: ");
            scanf("%d", &saque);
        
        case 2: // Depósito

        case 3: // Consultar Saldo

        default:

    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
