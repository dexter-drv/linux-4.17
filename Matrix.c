#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 10

// Define matrix size (adjust as needed)
#define ROWS_A 3
#define COLS_A 3
#define ROWS_B 3
#define COLS_B 3

// Matrices
int matrixA[ROWS_A][COLS_A];
int matrixB[ROWS_B][COLS_B];
int resultMatrix[ROWS_A][COLS_B];

// Structure to pass data to each thread
struct ThreadData {
    int row;
    int col;
};

// Function to multiply a specific row of matrix A by a specific column of matrix B
void *multiply(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    int row = data->row;
    int col = data->col;

    int sum = 0;
    for (int i = 0; i < COLS_A; ++i) {
        sum += matrixA[row][i] * matrixB[i][col];
    }

    resultMatrix[row][col] = sum;

    pthread_exit(NULL);
}

int main() {
    // Initialize matrices with some values (adjust as needed)
    for (int i = 0; i < ROWS_A; ++i) {
        for (int j = 0; j < COLS_A; ++j) {
            matrixA[i][j] = i + j;
        }
    }

    for (int i = 0; i < ROWS_B; ++i) {
        for (int j = 0; j < COLS_B; ++j) {
            matrixB[i][j] = i - j;
        }
    }

    // Display matrices A and B
    printf("Matrix A:\n");
    for (int i = 0; i < ROWS_A; ++i) {
        for (int j = 0; j < COLS_A; ++j) {
            printf("%d\t", matrixA[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < ROWS_B; ++i) {
        for (int j = 0; j < COLS_B; ++j) {
            printf("%d\t", matrixB[i][j]);
        }
        printf("\n");
    }

    // Multiply matrices using threads
    pthread_t threads[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < ROWS_A; ++i) {
        for (int j = 0; j < COLS_B; ++j) {
            struct ThreadData *data = (struct ThreadData *)malloc(sizeof(struct ThreadData));
            data->row = i;
            data->col = j;
            pthread_create(&threads[i][j], NULL, multiply, (void *)data);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < ROWS_A; ++i) {
        for (int j = 0; j < COLS_B; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Display the result matrix
    printf("\nResult Matrix:\n");
    for (int i = 0; i < ROWS_A; ++i) {
        for (int j = 0; j < COLS_B; ++j) {
            printf("%d\t", resultMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
