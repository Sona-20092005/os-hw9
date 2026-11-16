#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* compute_square(void* arg) {
    int* num = (int*)arg;
    int result = (*num) * (*num);

    printf("Square of %d is %d\n", *num, result);

    return NULL;
}

int main() {
    pthread_t threads[5];
    int arr[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, compute_square, (void*)&arr[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    return 0;
}
