#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_CLIENTS 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    pthread_t threads[NUM_CLIENTS];
    int *ids[NUM_CLIENTS];
    int i;

    for(i = 0;)

}
