#include <iostream>
#include "timer.hpp"
using namespace std;

#ifdef USING_MKL
#include <mkl.h>
#endif

#ifdef USING_OPENBLAS
extern"C" {
  #include <cblas.h>
}
#endif

// test time performance on large matrix multiplication with vector as baseline
// using cblas_?gemv API of BLAS
// the cblas_?gemv() function will call dyncamic library according to compilation falg.
int test_cblas_sgemv(int mrow, int mcol, int iteration) {

	// prepare a matrix and a vector
	int vsize = mcol;
	int outsize = mrow;

	float* matrix = new float[mrow*mcol];
	float* vector = new float[vsize];
	float* output = new float[outsize];

	memset(matrix, 0, mrow*mcol);
	memset(vector, 0, vsize);
	memset(output, 0, outsize);

	for(int i=0;i<mrow*mcol;i+=10){
		matrix[i] = (rand()%100)/100.0;
	}
	for(int i=0;i<vsize;i++){
		vector[i] = (rand()%100)/100.0;
	}
	// data preparation done.

	TIMER_BEGIN("using cblas_sgemv");

	// loop 100 to see time
	for(int i=0;i<iteration;i++){	
		// using gemv
		int m = mrow;
		int n = mcol;
		float alpha = 1.0;
		float beta = 1.0;

		// the matrix calculation
		// output = alpha*matrix*vector+beta*output
		cblas_sgemv(CblasRowMajor, CblasNoTrans,
					 m, n,
					 alpha, matrix, n, vector, 1, 
					 beta, output, 1);

	}
	TIMER_END("using cblas_sgemv");

	delete[] matrix;
	delete[] vector;
	delete[] output;

	return 0;
}

// test time performance on sparse matrix multiplication with vector
// using mkl_cspblas_scsrgemv API of BLAS
// the mkl_cspblas_?csrgemv() function will call mkl library.
// if mkl is not used during compilation, this function should be empty.
int test_mkl_cspblas_scsrgemv(int mrow, int mcol, int iteration) {

#ifdef USING_MKL

	// prepare data
	int vsize = mcol;
	int outsize = mrow;

	float* matrix = new float[mrow*mcol];
	float* vector = new float[vsize];
	float* output = new float[outsize];

	memset(matrix, 0, mrow*mcol);
	memset(vector, 0, vsize);
	memset(output, 0, outsize);

	for(int i=0;i<mrow*mcol;i+=10){
		matrix[i] = (rand()%100)/100.0;
	}
	for(int i=0;i<vsize;i++){
		vector[i] = (rand()%100)/100.0;
	}
	
	// using gemv
	int m = mrow;
	int n = mcol;
	float alpha = 1.0;
	float beta = 1.0;
	
	// to csr formmat
	int non0count = 0;
	for(int i=0;i<mrow;i++){
		for(int j=0;j<mcol;j++){
			if(matrix[i]!=0) non0count++;//!!!Maybe Wrong
		}
	}
	cout<<"sparsity: "<<1-1.0*non0count/(mrow*mcol)<<endl;
	float* a = new float[non0count];
	int* ja = new int[non0count];
	int* ia = new int[mrow+1]; ia[0] = 0;

	non0count = 0;
	for(int i=0;i<mrow;i++){
		ia[i+1] = ia[i];
		for(int j=0;j<mcol;j++){
			if(matrix[i]!=0){
				a[non0count] = matrix[i];
				ja[non0count] = j;
				ia[i+1]++;
			} 
		}
	}
	// data preparation done.

	TIMER_BEGIN("using mkl_cspblas_scsrgemv");

	for(int i=0;i<iteration;i++){	

		// the matrix calculation
		// output = alpha*matrix*vector+beta*output
		// but the matrix is presented in CSR format.
		
		// About MKL API
		// API document in
		// https://software.intel.com/en-us/mkl-developer-reference-c-mkl-cspblas-csrgemv

		// About CSR format
		// page 11 of https://www.bu.edu/pasi/files/2011/01/NathanBell1-10-1000.pdf
		// vividly shows what is CSR format.

		const char trans = 'N';
		mkl_cspblas_scsrgemv(&trans, &mrow,
							 a, ia, ja, 
							 vector, output);
	}

	TIMER_END("using mkl_cspblas_scsrgemv");

	delete[] matrix;
	delete[] vector;
	delete[] output;

	delete[] a;
	delete[] ja;
	delete[] ia;

#endif

	return 0;
}

int main(){

	srand(time(NULL));

	int matrix_row = 1024;
	int matrix_col = 11985;

	int iteration = 1000;
	cout<<"Runing iteration: "<<iteration<<endl;

	test_cblas_sgemv(matrix_row,matrix_col,iteration);
	test_mkl_cspblas_scsrgemv(matrix_row,matrix_col,iteration);

	return 0;
}