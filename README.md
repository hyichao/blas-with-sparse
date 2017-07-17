# blas-with-sparse
Implementing matrix calculation using different BLAS and test time performance.

### Install openblas

use command line
```
sudo apt-get install libopenblas-dev
```

if everything goes fine, openblas will be installed into /usr/lib/

### Install MKL
Please follow [Intel's instruction](https://software.intel.com/en-us/mkl)
If nothing wrong happens, mkl will be installed into /opt/intel/mkl/

### Clone Project

```
git clone https://github.com/hyichao/blas-with-sparse.git
```

## Use Openblas to test common matrix calculation as baseline

### How to Run?
Inside the project，two shell script is available.  

If you want to run with openblas, please enter the project and run

```
sh run-with-openblas.sh
```

The path and link flag may not be suitable for someone who install openblas in custom way. If so, modify the path.

## Use MKL to test common matrix calculation
Different BLAS offer same API for most often used calculation.  
i.e. Matrix * Vector  

```
cblas_sgemv()
cblas_dgemv()
...
```
Just to mention, when letter 'd' is put in front of 'gemv', data is stored as double; when the letter is 's', data is stored as float.

### How to Run?
Inside the project，two shell script is available.  

If you want to run with openblas, please enter the project and run

```
sh run-with-mkl.sh
```

The path and link flag may not be suitable for someone who install mkl in custom way. If so, modify the path.

## USE MKL to test sparse matrix calculation.
When it comes to neural network compression issue, the most important topic is how to do calculation with sparse matrix.  

mkl offers API 

```
mkl_cspblas_?csrgemv ()  
```

This API require matrix data stored in CSR format.  
About CSR format, I personally recommand reading this [pdf](https://www.bu.edu/pasi/files/2011/01/NathanBell1-10-1000.pdf).

### How to Run?
Same with above

## TEST 
Testing time with 1000 iterations of **1024*11985 matrix** 

|   BLAS     | common | sparse |
| ---------- | ---    | ---
| OpenBlas   | 3719.309 ms | /   |
| MKL        | 3002.197 ms | 227.752 |
| Atlas      |  TODO |  TODO   |
