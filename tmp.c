#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_barrier_t barrier;

int A[2][2] = {2, 1, 5, 7};
int b[] = {11, 12};
int x[2] = {1, 1};

void *Jacobi(void *threadid);


int main() {
    int n;
    scanf("%d", &n);
    pthread_t threads[n];
    int *ids[n];
    pthread_barrier_init(&barrier, NULL, n);

    for(int i = 0; i < n; i++) {
        ids[i] = (int *) malloc(sizeof(int));
        *ids[i] = i;
        pthread_create(&threads[i], NULL, Jacobi, (void *) ids[i]);
    }
    for(int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);
    pthread_exit(NULL);
}


void *Jacobi(void *threadid) {
    int k = 0;

    while(k < 10) {
        for(int i = 0; i < 2; i++) {
            int sum;
            for(int j = 1; j < 3; j++) {
                if(j != i) {
                    sum = A[i][j] * x[j];
                }
            }
            printf("%d\n")
            x[i] = (1/A[i][i]) * (b[i] - sum); //x[i] no tempo k+1
            printf("No tempo %d, Thread %d calculou que x[%d] = %d\n", k+1, *((int *)threadid), i, x[i]);
        }

        pthread_barrier_wait(&barrier);
        k++;
    }
}
