#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int matrixSize[5] = {250, 500, 750, 1000, 2000};
    
    for(int k = 0; k < 5; k++) {
        int matSize = matrixSize[k];
        int rows = matSize / 2;
        int cols = matSize / 2;

        int** A = (int**)malloc(rows * sizeof(int*));
        int** B = (int**)malloc(rows * sizeof(int*));
        for(int i = 0; i < rows; i++) {
            A[i] = (int*)malloc(cols * sizeof(int));
            B[i] = (int*)malloc(cols * sizeof(int));
        }

        srand((unsigned int)time(NULL));
        int mini = -100;
        int maxi = 100;

        int** C = (int**)malloc(rows * sizeof(int*));
        for(int i = 0; i < rows; i++) {
            C[i] = (int*)malloc(cols * sizeof(int));
        }

		clock_t start,end;
		start = clock();
		omp_set_num_threads(8);
		#pragma omp parallel for collapse(2)
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                A[i][j] = mini + rand() % (maxi - mini + 1);
                B[i][j] = mini + rand() % (maxi - mini + 1);
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        end = clock();
        
        double timeRequired = 1.0*(end - start) / CLOCKS_PER_SEC;
        
        printf("For %d size it took \t %f sec\n",matSize,timeRequired);

        for(int i = 0; i < rows; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
    }

    return 0;
}

