/***********************
* Name: Lior Bazak
* ID: 207106709
* Assignment: ex_6
***********************/

#include "sorting.h"

/*************************************************************************************************************
* Function Name: quicksort ****TAKEN FROM THE EX, BUG FIXED AND CHANGED TO BE GENERIC****
* Input: void* arr, int start, int stop, void(*swap)(void*, int, int), int(*compare)(void*, int, int)
* Output: none
* Function Operation: the function goes through an array, and sort it according to the comparison chosen
**************************************************************************************************************/
void quicksort(void* arr, int start, int stop, void(*swap)(void*, int, int), int(*compare)(void*, int, int)){
    //stop if the start index bigger/ equals the stop index
    if (start >= stop - 1) {
        return;
    }
    int pivot = start;
    int i = start, j = stop - 1;
    while (i < j) {
        /*
         * if the arr[i] item smaller than the pivot and we didnt passed the other index
         * continue forward with the index to the next item
         */
        while (compare(arr, i, pivot) <= 0 && i < stop - 1) {
            i++;
        }
        //if the first item bigger than the pivot- continue backwards with the index to the next item
        while (compare(arr, j, pivot) > 0) {
            j--;
        }
        if (i < j) {
            swap(arr, i, j);
        }
    }
    //move pivot to its place
    swap(arr, pivot, j);
    //do it again recursively on the 2 halfs created
    quicksort(arr, start, j, swap, compare);
    quicksort(arr, i, stop, swap, compare);
}

