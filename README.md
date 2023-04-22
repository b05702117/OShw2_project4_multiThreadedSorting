# Introduction

This program sorts an array of integers using multi-threading. The program uses two sorting threads to sort two halves of the array using the insertion sort algorithm, and a third merging thread to merge the sorted halves. The program implements the sorting algorithm using POSIX threads.

# Usage

```bash
gcc -o multithreadedSorting multithreadedSorting.c -pthread
./multithreadedSorting
```

# output

Upon execution, the program will output the original array, followed by the sorted array

```bash
original array:
22, 19, 42, 17, 25, 4, 14, 8
sorted array:
4, 8, 14, 17, 19, 22, 25, 42
```
