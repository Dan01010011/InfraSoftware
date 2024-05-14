#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_CLIENTS 6

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;

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


void put(int threadid){
    int v = rand() % 5000;
    pthread_mutex_lock(&mutex);
    printf("Cliente %d depositando: %d\n", threadid, v);

    // while(items == BUFFER_SIZE) {
    //     pthread_cond_wait(&empty, &mutex);
    
    // }
    *account[threadid] += v;
    printf("Novo saldo: %d\n", *account[threadid]);
    
    // if(*account[threadid] == 1) { 
    //     pthread_cond_broadcast(&fill); 
    // }
        
    pthread_mutex_unlock(&mutex); 
}

void get(int threadid) {
    int saque = rand() % 1000;
    pthread_mutex_lock(&mutex);
    printf("Cliente %d sacando: %d\n", threadid, saque);

    if(saque > *account[threadid]) {
        printf("Saldo insuficiente\n");
        pthread_exit(NULL);
    }
	
	// while(*account[threadid] == 0) {  
    //     pthread_cond_wait(&fill, &mutex); 
    // }
  
    *account[threadid] -= saque;
    printf("Novo saldo: %d\n", *account[threadid]);
  
    //if(items == BUFFER_SIZE - 1){ pthread_cond_signal(&empty); }
    
    pthread_mutex_unlock(&mutex);
}

void *operations(void *threadid) {
    int operation;
    operation = rand() % 3; //printf("%d\n", operation);

    switch(operation) {
        case 0: // Saque
            get(*((int *) threadid));
            break;  
        case 1: // Depósito
            put(*((int *) threadid));
            break;
        case 2: // Consultar Saldo
            pthread_mutex_lock(&mutex);
            printf("Cliente %d, seu saldo atual eh: %d\n", *((int *) threadid), *account[*((int *) threadid)]);
            pthread_mutex_unlock(&mutex);
            break;        
        default:
            printf("Operacao invalida\n");
            break;
    }

    pthread_exit(NULL);
}
