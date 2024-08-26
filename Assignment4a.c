#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define N 1000

int main(){

	long long int A[N] = {0};
	A[0] = 0;
	A[1] = 1;
	
	
	clock_t start,end;
	start = clock();
	#pragma omp parallel for
	for(int i = 2 ; i < N; i++){
		#pragma omp critical
		{
			A[i] = A[i - 1] + A[i - 2];
		}
	}
	end = clock();
	
	for(int i = 0 ; i < 100 ; i++)
		printf("%lld\t",A[i]);
	
	printf("%f\n",1.0*(end - start)/CLOCKS_PER_SEC);
}
