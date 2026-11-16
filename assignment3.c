#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_one_to_five(void* arg) {
    pthread_t tid = pthread_self();
    for (int i = 0; i < 5; i++) {
        printf("TID %lu: %d\n", (unsigned long)tid, i+1);
    }
    return NULL;
}

int main() {
    pthread_t threads[3];

    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, print_one_to_five, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    return 0;
}

