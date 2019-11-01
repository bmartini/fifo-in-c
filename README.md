# Implementing a FIFO in C

The FIFO is of fixed size and will drop data if full.



## Build Test Program

gcc fifo.c test.c



## Static Analysis

valgrind --tool=memcheck ./a.out


splint +matchanyintegral fifo.c test.c
