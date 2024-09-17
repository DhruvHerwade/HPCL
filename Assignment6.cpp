#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

#define N 10

vector<vector<long long>> C(N,vector<long long>(N,0));
vector<long long> K(N,0);

void matrixMatrixMultiplication(vector<vector<long long>> &A,vector<vector<long long>> &B){

	//#pragma omp parallel for collapse(2)
	for(int i = 0 ; i < N ; i++){
		
		for(int j = 0 ; j < N ; j++){
			
			for(int k = 0 ; k < N ; k++){
			
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void matrixVectorMultiplication(vector<vector<long long>> &A,vector<long long> &V){
	
	#pragma omp parallel for
	for(int i = 0 ; i < N ; i++){
		
		for(int j = 0 ; j < N ; j++){
			K[i] += A[i][j] * V[j];
		}
		//cout << omp_get_thread_num() << endl;
	}
}

void printMatrix(vector<vector<long long>> &v){
	
	for(int i = 0 ; i < N ; i++){
		for(int j = 0 ; j < N ; j++)
			cout << v[i][j] << " ";
		cout << endl;
	}
}

int main(){

	vector<vector<long long>> A(N,vector<long long>(N,0));
	vector<vector<long long>> B(N,vector<long long>(N,0));	
	
	vector<long long> V(N,0);
	
	srand(time(NULL));
	
	for(int i = 0 ; i < N ; i++){
		
		for(int j = 0 ; j < N ; j++){
			A[i][j] = rand() % 100;
			B[i][j] = rand() % 100;
		}
		V[i] = rand() % 100;
	}
	
	double st,ed;
	st = omp_get_wtime();
	matrixMatrixMultiplication(A,B);
	ed = omp_get_wtime();
	
	cout << "Matrix A is:" << endl;
	printMatrix(A);
	cout << "Matrix B is:" << endl;
	printMatrix(B);
	cout << "Matrix C is:" << endl;
	printMatrix(C);	
	
	cout << "Time required for computation of matrix-matrix multiplication is: " << (ed - st) * 1000 << " milliseconds" << endl << endl << endl;	
	
	
	st = omp_get_wtime();
	matrixVectorMultiplication(A,V);
	ed = omp_get_wtime();
	
	cout << "Matrix is: " << endl;
	for(int i = 0 ; i < N ; i++)
		cout << K[i] << " ";
	cout << endl;
	
	
	cout << "Time required for computation of matrix-vector multiplication is: " << (ed - st) * 1000 << " milliseconds" << endl;	


}
