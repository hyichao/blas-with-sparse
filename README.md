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


## Use Openblas to test common matrix calculation as baseline

## Use MKL to test common matrix calculation.
Different BLAS offer same API for most often used calculation.  
i.e. Matrix * Vector  
cblas\_?gemv()

Just to mention, when ? is 'd', data is stored as double; when ? is 's', data is stored as float.

## USE MKL to test sparse matrix calculation.
When it comes to neural network compression issue, the most important topic is how to do calculation with sparse matrix.  

mkl offers API mkl\_cspblas\_?csrgemv ()  

This API require matrix data stored in CSR format.  
About CSR format, I personally recommand reading this [pdf](https://www.bu.edu/pasi/files/2011/01/NathanBell1-10-1000.pdf).

