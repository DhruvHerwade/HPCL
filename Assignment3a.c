#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void understanding_schedule() {
    int i;
    #pragma omp parallel for schedule(static, 2)
    for (i = 0; i < 10; i++) {
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    
    // total number of iterations => 10
    // each thread will get 2 iterations (chunk), so we will have a total of 5 threads

    printf("\n\n");
    
    #pragma omp parallel for schedule(dynamic, 2)
    for (i = 0; i < 10; i++) {
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }
    // each thread will get 2 iterations but not necessary that the thread0 will get the 
    // 0th and 1st iteration, guided is similar to dynamic but the chunk size reduces gradually

}

void understanding_nowait(){
	
	#pragma omp parallel
	{
		
		#pragma omp for nowait
		for(int i = 0 ; i < 10 ; i++){
			printf("%d iteration of thread %d\n", i, omp_get_thread_num());
		}
		printf("Work done by %d\n", omp_get_thread_num());
		// this statement will be printed as soon as a thread has finished it's execution
		// if nowait then we find all the prints statements together
	}

}

void understanding_reduction(){

	int sum = 0;
	
	#pragma omp parallel for reduction(+:sum)
	for(int i = 1 ; i <= 10 ; i++)
		sum += i;
	// if no reduction then sum is shared among the threads and the end value will be
	// dependent upon thread operations => race condition
	// to prevent this use reduction(operator : variable)
	// variable => copy to each thread
	// operator => how these variables be combined with the original one
		
	printf("%d\n", sum);
}

void understanding_ordered(){

	#pragma omp parallel for ordered
	for(int i = 0 ; i < 10 ; i++)
		#pragma omp ordered
		printf("%d executed by %d\n",i,omp_get_thread_num());
		
	// The ordered clause allows iterations to be executed in the order 
	// they would have been in a sequential execution, even in a parallel loop.
}

void understanding_collapse(){

	#pragma omp parallel for collapse(2)
	for(int i = 1 ; i < 2 ; i++)
		for(int j = 1 ; j < 10 ; j++)
			printf("%d * %d = %d\t executed by %d\n",i,j,i*j,omp_get_thread_num());
}

int compareAsc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compareDesc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

void usingInMinScaler(){

	int A[1000];
	int B[1000];
	
	srand(time(NULL));
	
	int min = -100;
	int max = 100;
	
	for(int i = 0 ; i < 1000 ; i ++){
		
		A[i] = min + rand() % (max - min + 1);
		B[i] = min + rand() % (max - min + 1);
		
//		printf("%d %d\n",A[i],B[i]);
	}
	
	qsort(A, 1000, sizeof(int), compareAsc);
    qsort(B, 1000, sizeof(int), compareDesc);
    
//    for(int i = 0 ; i < 10 ; i++)
//    	printf("%d %d\n",A[i],B[i]);

	int minScalarSum = 0;
	
	#pragma omp parallel for schedule(guided) reduction(+:minScalarSum)
	for(int i = 0 ; i < 1000 ; i++){
		minScalarSum += A[i] * B[i];
//		printf("%d performed by %d\n",i,omp_get_thread_num());
	}
	printf("Min Scalar Sum : %d\n", minScalarSum);
	
	//minScalarSum = 0;
	/*for(int i = 0 ; i < 1000 ; i++){
		minScalarSum += A[i] * B[i];
	}
	printf("Min Scalar Sum : %d\n", minScalarSum);
	*/
	
}

int main(){

	understanding_schedule();
	understanding_nowait();
	understanding_reduction();
	understanding_collapse();
	understanding_ordered();
	
	
	usingInMinScaler();
}

