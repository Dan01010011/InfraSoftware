#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_CLIENTS 7

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
    

    pthread_exit(NULL);
}


int put(int threadid){
    int v = rand() % 5000;
    pthread_mutex_lock(&mutex);

    // while(items == BUFFER_SIZE) {
    //     pthread_cond_wait(&empty, &mutex);
    
    // }
    *account[threadid] += v;
    
    // if(*account[threadid] == 1) { 
    //     pthread_cond_broadcast(&fill); 
    // }
        
    pthread_mutex_unlock(&mutex);
    return v; 
}

int get(int threadid) {
    int saque = rand() % 1000;
    pthread_mutex_lock(&mutex);

    if(saque > *account[threadid]) {
        printf("Saldo insuficiente\n");
        pthread_exit(NULL);
    }
	
	// while(*account[threadid] == 0) {  
    //     pthread_cond_wait(&fill, &mutex); 
    // }
  
    *account[threadid] -= saque;
  
    //if(items == BUFFER_SIZE - 1){ pthread_cond_signal(&empty); }
    
    pthread_mutex_unlock(&mutex);
    return saque;
}

void *operations(void *threadid) {
    int operation;
    operation = rand() % 3; //printf("%d\n", operation);

    switch(operation) {
        case 0: // Saque
            int s = get(*((int *) threadid));
            printf("Cliente %d sacando: %d...(Novo saldo: %d)\n", *((int*) threadid), s, *account[*((int *) threadid)]);
            break;  
        case 1: // Depósito
            int p = put(*((int *) threadid));
            printf("Cliente %d depositando: %d...(Novo saldo: %d)\n", *((int*) threadid), p, *account[*((int *) threadid)]);
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
