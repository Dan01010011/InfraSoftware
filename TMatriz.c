#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 2
#define LINHAS 3
#define COLUNAS 3

int A[3][3] = { {1, 2,5}, {3, 4,2}, {5, 6,1} };
int B[3][3] = { {1, 2,5}, {3, 4,2}, {5, 6,1} };
int R[3][3];

void *threadCode(void *tid) {
    int i, j, k;
    long threadId = (*(long *) tid);

    for(i = threadId; i < LINHAS; i = i + NUM_THREADS) {
        for(j = 0; j < COLUNAS; j++) {
            R[i][j] = 0;
            for(k = 0; k < COLUNAS; k++) {
                R[i][j] = A[i][j] + B[i][k] * matriz2[k][j];
            }
        }
    }
}


int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    long *taskids[NUM_THREADS];
    int i, j;

    for(i = 0; i < NUM_THREADS; i++) {
        taskids[i] = (long *) malloc(sizeof(long));
        *taskids[i] = i;
        pthread_create(&threads[i], NULL, threadCode, (void *) taskids)
    }

}
