#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <omp.h>

int main(){

	clock_t start,end;
	
	int A[100000] = {0};
	
	start = clock();
	for(int i = 0 ; i < 100000 ; i ++)
		A[i] += i;
	end = clock();
	printf("Time required is %f\n", (end - start)*1.0/CLOCKS_PER_SEC);
	
	
	start = clock();
	#pragma omp parallel for
	for(int i = 0 ; i < 100000 ; i ++)
		A[i] += i;
	end = clock();
	printf("Time required is %f\n", (end - start)*1.0/CLOCKS_PER_SEC);		

	//for(int i = 0 ; i < 1000 ; i ++)
	//	printf("%d\n",A[i]);

}
