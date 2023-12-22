#include <stdio.h>
#include <pthread.h>

// Function to be executed by each thread
void *printThreadID(void *threadID) {
    long tid = (long)threadID;
    printf("Thread ID: %ld\n", tid);
    syscall(549);
    while(1);
    pthread_exit(NULL);
}

int main() {
    // Number of threads to create
    const int numThreads = 15;

    // Thread ID array
    pthread_t threads[numThreads];

    // Create and launch threads
    for (long i = 0; i < numThreads; i++) {
        int createThreadStatus = pthread_create(&threads[i], NULL, printThreadID, (void *)i);
        if (createThreadStatus) {
            fprintf(stderr, "Error creating thread %ld. Return code: %d\n", i, createThreadStatus);
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

