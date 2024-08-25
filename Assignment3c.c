#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define VECTOR_SIZE 200
#define SCALAR 10
#define SIZE 1000

void vector_add_static(int chunk_size) {
    int *vector = (int *)malloc(VECTOR_SIZE * sizeof(int));
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = rand() % 100;
    }
    
    double start_time = omp_get_wtime();
    omp_set_num_threads(8);
    #pragma omp parallel for schedule(static, chunk_size)
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] += SCALAR;
    }
    double end_time = omp_get_wtime();
    
    printf("Static Schedule with Chunk Size %d: %f seconds\n", chunk_size, end_time - start_time);
    
    free(vector);
}

void vector_add_dynamic(int chunk_size) {
    int *vector = (int *)malloc(VECTOR_SIZE * sizeof(int));
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = rand() % 100;
    }
    
    double start_time = omp_get_wtime();
    omp_set_num_threads(8);
    #pragma omp parallel for schedule(dynamic, chunk_size)
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] += SCALAR;
    }
    double end_time = omp_get_wtime();
    
    printf("Dynamic Schedule with Chunk Size %d: %f seconds\n", chunk_size, end_time - start_time);
    
    free(vector);
}

void using_nowait(){

	
    int i;
    int array[SIZE];
    double start_time, end_time;

    for (i = 0; i < SIZE; i++) {
        array[i] = i;
    }
    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i = 0; i < SIZE; i++) {
            array[i] += 1;
        }
        #pragma omp for
        for (i = 0; i < SIZE; i++) {
            array[i] *= 2;
        }
    }

    end_time = omp_get_wtime();

    printf("Time taken: %f seconds\n", end_time - start_time);
}

int main() {
    srand(time(NULL));

    int chunk_sizes[] = {1, 2, 4, 8, 16};
    int num_chunks = sizeof(chunk_sizes) / sizeof(chunk_sizes[0]);

    for (int i = 0; i < num_chunks; i++) {
        vector_add_static(chunk_sizes[i]);
    }
    
    for (int i = 0; i < num_chunks; i++) {
        vector_add_dynamic(chunk_sizes[i]);
    }
    
    using_nowait();

    return 0;
}

