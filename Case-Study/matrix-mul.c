#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate a 2D matrix on the heap
double **allocate_matrix(int size)
{
    double **matrix = (double **)malloc(size * sizeof(double *));
    if (matrix == NULL)
    {
        perror("Failed to allocate memory for matrix rows");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (double *)malloc(size * sizeof(double));
        if (matrix[i] == NULL)
        {
            perror("Failed to allocate memory for matrix columns");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

// Function to free the memory of a 2D matrix
void free_matrix(double **matrix, int size)
{
    if (matrix == NULL)
        return;
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to initialize matrices with random values
void initialize_matrices(double **A, double **B, double **C, int size)
{
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = (double)rand() / (double)RAND_MAX;
            C[i][j] = 0.0;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0)
    {
        fprintf(stderr, "Matrix size must be a positive integer.\n");
        return 1;
    }

    printf("Initializing matrices of size %d x %d...\n", n, n);

    // 1. Allocate memory on the heap
    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);
    double **C = allocate_matrix(n);

    initialize_matrices(A, B, C, n);

    printf("Performing matrix multiplication...\n");

    // 2. Use modern, high-resolution timer
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // 3. Optimized matrix multiplication loop (ikj order)
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            double r = A[i][k]; // Small optimization
            for (int j = 0; j < n; j++)
            {
                C[i][j] += r * B[k][j];
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate elapsed time
    double time_taken = (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);

    printf("Multiplication finished in %0.6f seconds.\n", time_taken);

    // 4. Free all dynamically allocated memory
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}