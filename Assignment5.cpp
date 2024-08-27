#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>
using namespace std;

void Q1(){

	#pragma omp parallel
	{
	
		#pragma omp sections
		{
		
			 #pragma omp section
            {
                #pragma omp critical
                {
                    cout << "Dhruv" << " " << omp_get_thread_num() << endl;
                }
            }
            #pragma omp section
            {
                #pragma omp critical
                {
                    cout << "Ritu" << " " << omp_get_thread_num() << endl;
                }
            }
            #pragma omp section
            {
                #pragma omp critical
                {
                    cout << "Shrutika" << " " << omp_get_thread_num() << endl;
                }
            }
            #pragma omp section
            {
                #pragma omp critical
                {
                    cout << "Satish" << " " << omp_get_thread_num() << endl;
                }
            }
			
			
		}
	}

}

void Q2(){

	int sum = 0;
	#pragma omp parallel reduction(+:sum)
	{
		#pragma omp critical
		{
			cout << omp_get_thread_num()*omp_get_thread_num() << endl;
			sum += omp_get_thread_num()*omp_get_thread_num();
		}
	}
	cout << sum << endl;

}

void Q3(){
	
	int Aryabhatta=10;
	#pragma omp parallel firstprivate(Aryabhatta)
	{
		#pragma omp critical
		{
			cout << omp_get_thread_num() * Aryabhatta << endl;
		}
	}

}

void Q4(){

	int total_sum = 0;
    int n = 20;

    #pragma omp parallel
    {
        int partial_sum = 0;

        #pragma omp for
        for (int i = 1; i <= n; i++) {
            partial_sum += i;
        }

        #pragma omp critical
        total_sum += partial_sum;
    }

	cout << "The total sum of the first "<< n << " natural numbers is " << total_sum << endl;


}

void matrix_multiply_static_parallel(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int N) {
	omp_set_num_threads(12);
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_static(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int N) {
	//omp_set_num_threads(8);
    //#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void Q5(){
	
	int N = 1000;
	vector<std::vector<int>> A(N, std::vector<int>(N, 1));
	vector<std::vector<int>> B(N, std::vector<int>(N, 1));
	vector<std::vector<int>> C(N, std::vector<int>(N, 0));
	auto start = std::chrono::high_resolution_clock::now();
    matrix_multiply_static(A, B, C, N);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto start2 = std::chrono::high_resolution_clock::now();
    matrix_multiply_static_parallel(A, B, C, N);
    auto end2 = std::chrono::high_resolution_clock::now();
    
    chrono::duration<double> elapsed = end - start;
	cout << "Sequential scheduling execution time: " << elapsed.count() << " seconds" << endl;
		    chrono::duration<double> elapsed2 = end2 - start2;
		cout << "Dynamic scheduling execution time: " << elapsed2.count() << " seconds" << endl;
		
		auto speedup = elapsed.count() / elapsed2.count();
		cout <<"Speed up: " <<speedup << endl;

}

void print_series_2() {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 1: %d\n", 2 * i);
    }
}

void print_series_4() {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 2: %d\n", 4 * i);
    }
}

void Q6() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            print_series_2();
        }

        #pragma omp section
        {
            print_series_4();
        }
    }

}

void Q7(){
	
	int n = 1000;
    int arr[n];
    int total_sum = 0;

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
//        #pragma omp critical
        {
            total_sum += arr[i];
        }
    }
    
    cout << "Sum of first " << n << " numbers is " <<total_sum << endl;
}

void Q8(){

	int n = 100000000;
    int *arr = (int*)malloc(n * sizeof(int));
    long long total_sum = 0;

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

	double start,end;
	start = omp_get_wtime();
    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }
    end = omp_get_wtime();
    
    cout << "Time required is: " << (end - start) << endl;
   	cout << "Sum of first " << n << " numbers is " <<total_sum << endl; 
}

int main(){


	/*Q1();
	cout << endl;
	Q2();
	cout << endl;
	Q3();
	cout << endl;
	Q4();
	cout << endl;
	Q5();
	cout << endl;
	Q6();
	cout << endl;
	Q7();
	cout << endl;
	Q8();
	cout << endl;
	*/
	Q5();

}
