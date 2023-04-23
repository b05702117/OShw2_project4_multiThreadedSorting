# Parallel Merge Sort

## Introduction

This program implements a parallel version of the Merge Sort algorithm, which sorts an array of integers in ascending order.

The program generates an array of size ARRAY_SIZE with random integer values between 0 and 49 (inclusive) using the initArray() function. The number of threads used for sorting is defined by NUM_THREADS.

The first two threads sort the left and right halves of the array using the insertionSort() function in parallel. Once the sorting threads have completed, the third thread merges the two sorted halves using the merge() function. 

The program prints the original array before sorting and the sorted array after sorting. Note that the array is generated randomly, so the output might be different every time the program is executed.

## Usage

Compile the program using the following command:
```
gcc -o multithreadedSorting multithreadedSorting.c -pthread
```

Run the program with the following command:
```
./multithreadedSorting
```

## output

Since the program generates an array randomly, the output may vary each time the program is run. Below is an example output for reference:

```bash
original array:
44, 42, 25, 26, 32, 32, 15, 40
sorted array:
15, 25, 26, 32, 32, 40, 42, 44
```
