#!/usr/bin/env sh

CXX=g++
INCLUDE=-I/usr/include
LINK_FLAG=-L/usr/lib 
LD_FLAG=-lopenblas

${CXX} gemv.cpp ${INCLUDE} ${LINK_FLAG} ${LD_FLAG} -DUSING_OPENBLAS -o executable.out
./executable.out

#valgrind --tool=memcheck --track-origins=yes ./executable.out
