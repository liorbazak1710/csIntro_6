#ifndef SORTING_H
#define SORTING_H

// including start, excluding stop
void quicksort(void* arr, int start, int stop, void(*swap)(void*, int, int), int(*compare)(void*, int, int));

#endif
