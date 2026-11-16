#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARRAY_SIZE 50
#define NUM_THREADS 2

int array[ARRAY_SIZE];

void* sum_array(void* arg) {
    int thread_id = *((int*)arg);

    int sum = 0;

    for (int i = thread_id * (ARRAY_SIZE / NUM_THREADS); i < (thread_id + 1) * (ARRAY_SIZE / NUM_THREADS); i++) {
        sum += array[i];
    }

    printf("Thread %d: %d\n", thread_id, sum);
    return NULL;
}

int main() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i+1;
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("Partial sums\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if(pthread_create(&threads[i], NULL, sum_array, (void*)&thread_ids[i]) != 0){
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if(pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    return 0;
}
