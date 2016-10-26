@echo off
cls

g++ -I.\ -I.\Program03Files\CSC2110 -c RadixSortDriver.cpp
g++ -L.\Program03Files\CSC2110 -o RadixSort.exe RadixSortDriver.o -lCSC2110
