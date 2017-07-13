#!/usr/bin/env sh

CXX=g++
INCLUDE=-I/opt/intel/mkl/include
LINK_FLAG=-L/opt/intel/mkl/lib/intel64 
LD_FLAG=-lmkl_rt

${CXX} gemv.cpp ${INCLUDE} ${LINK_FLAG} ${LD_FLAG} -DUSING_MKL -o executable.out
./executable.out

#valgrind --tool=memcheck --track-origins=yes ./executable.out
