#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(){
	
	printf("Enter number of threads: ");
	int numThreads;
	scanf("%d",&numThreads);
	
	omp_set_num_threads(numThreads);
	
	clock_t start,end;
	start = clock();
	#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		printf("Hello World from %d\n",tid);
	}
	end = clock();
	
	printf("Time required is %f seconds\n", (end - start)*1.0/CLOCKS_PER_SEC);
	
	
	start = clock();
	for(int i = 0 ; i < numThreads ; i++)
		printf("Hello World %d\n",i);
	end = clock();
	
	printf("For sequential it took %f seconds \n", (end - start)*1.0/CLOCKS_PER_SEC);
	
	//int maxThreads = omp_get_max_threads();
	//printf("%d\n",maxThreads);
	
}
