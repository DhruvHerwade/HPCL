#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>

int main_org(){

	int totalPoints = 10000000;
	int insideCircle = 0;
	
	srand(time(0));
	
	clock_t start,end;	
	start = clock();
	#pragma omp parallel for
	for(int i = 0 ; i < totalPoints ; i++){
	
		double x = 1.0*rand()/RAND_MAX;
		double y = 1.0*rand()/RAND_MAX;
		
		if(x*x + y*y <= 1.0)
			insideCircle++;
		
	}
	end = clock();
	printf("Time required %f\n",1.0*(end - start)/CLOCKS_PER_SEC);
	double valueOfPi = 4.0 * insideCircle / totalPoints;
	printf("%f\n", valueOfPi);

}
// The above method doesn't work because the rand() is not thread safe
// and we might be getting repeated points during this
// also the use of shared insideCircle may lead to race condition and not accurate results







int main() {
    int totalPoints = 10000000;
    int insideCircle = 0;

    double start, end;
    start = omp_get_wtime();

    // this directive is essential and means:
    // each thread should create a copy of insideCircle => to avoid race condition
    // at the end of the // region they will safely combine the results in insideCircle
    #pragma omp parallel for reduction(+:insideCircle)
    for(int i = 0; i < totalPoints; i++) {
        unsigned int thread_seed = time(NULL) ^ (omp_get_thread_num() + i);

        double x = (double)rand_r(&thread_seed) / RAND_MAX;
        double y = (double)rand_r(&thread_seed) / RAND_MAX;
        
        if (x * x + y * y <= 1.0) {
            insideCircle++;
        }
    }

    end = omp_get_wtime();
    printf("Time required: %f seconds\n", end - start);

    double valueOfPi = 4.0 * insideCircle / totalPoints;
    printf("Estimated value of Pi: %f\n", valueOfPi);

    return 0;
}

