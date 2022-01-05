#include "sorting.h"

void quicksort(void* arr, int start, int stop, void(*swap)(void*, int, int), int(*compare)(void*, int, int)){
    if (start >= stop - 1) {
        return;
    }
    int pivot = start;
    int i = start, j = stop - 1;
    while (i < j) {
        while (compare(arr, i, pivot) <= 0 && i < stop - 1) {
            i++;
        }
        while (compare(arr, j, pivot) > 0) {
            j--;
        }
        if (i < j) {
            swap(arr, i, j);
        }
    }
    swap(arr, pivot, j);
    quicksort(arr, start, j, swap, compare);
    quicksort(arr, i, stop, swap, compare);
}

