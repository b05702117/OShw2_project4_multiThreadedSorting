#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <limits.h> // to include INT_MAX

#define ARRAY_SIZE 8
#define NUM_THREADS 3

/* global variables shared by threads */
int array[ARRAY_SIZE];

typedef struct {
    int start; // index for the start
    int end;   // index for the end
} Parameters;

void* insertionSort(void* arg) {
    Parameters* args = (Parameters*) arg;
    int start = args->start;
    int end = args->end;

    int i, key, j;
    for (i = start + 1; i <= end; i++) {
        key = array[i];
        j = i  - 1;
        while (j >= start && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }

    pthread_exit(NULL);
}

void* merge(void* arg) {
    Parameters* args = (Parameters*) arg;
    int start = args->start;
    int end = args->end;

    int mid = (start + end) / 2;
    int len1 = mid - start + 1;
    int len2 = end - mid;
    int* left_array = (int*) malloc((len1 + 1) * sizeof(int));
    int* right_array = (int*) malloc((len2 + 1) * sizeof(int));

    for (int i = 0; i < len1; i++) {
        left_array[i] = array[start + i];
    }
    for (int j = 0; j < len2; j++) {
        right_array[j] = array[(mid + 1) + j];
    }
    left_array[len1] = INT_MAX;
    right_array[len2] = INT_MAX;

    int i = 0;
    int j = 0;
    for (int k = start; k <= end; k++) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        }
        else {
            array[k] = right_array[j];
            j++;
        }
    }

    free(left_array);
    free(right_array);

    pthread_exit(NULL);
}

void initArray() {
    srand(time(NULL));

    int num;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        num = rand() % 50; // randomly generate integer within 50
        array[i] = num;
    }

    // int num = ARRAY_SIZE;
    // for (int i = 0; i < ARRAY_SIZE; i++) {
    //     array[i] = num;
    //     num--;
    // }
}

void printArray(int* array, int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d\n", array[n-1]);
}

int main() {
    initArray();
    printf("original array:\n");
    printArray(array, ARRAY_SIZE);

    pthread_t thread_sorting_1, thread_sorting_2, thread_merging;
    Parameters thread_paras_1, thread_paras_2, thread_merging_paras;

    int start, end, mid;
    start = 0;
    end = ARRAY_SIZE - 1;
    mid = (start + end) / 2;

    // printf("start: %d, mid: %d, end: %d\n", start, mid, end);

    thread_paras_1.start = start;
    thread_paras_1.end = mid;

    thread_paras_2.start = mid + 1;
    thread_paras_2.end = end;

    pthread_create(&thread_sorting_1, NULL, insertionSort, &thread_paras_1);
    pthread_create(&thread_sorting_2, NULL, insertionSort, &thread_paras_2);

    // wait until the sorting threads finish execution
    pthread_join(thread_sorting_1, NULL);
    pthread_join(thread_sorting_2, NULL);

    // printf("after two sorting threads:\n");
    // printArray(array, ARRAY_SIZE);

    thread_merging_paras.start = start;
    thread_merging_paras.end = end;

    pthread_create(&thread_merging, NULL, merge, &thread_merging_paras);
    pthread_join(thread_merging, NULL);

    printf("sorted array:\n");
    printArray(array, ARRAY_SIZE);

    pthread_exit(NULL);

    return 0;
}