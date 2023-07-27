#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21
/**
 * TODO add documentation
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

//sorts buslines using bubble sort sorting algorithm
void bubble_sort (BusLine *start, BusLine *end);

//sorts buslines using quick sort sorting algorithm
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

//partition function, helper for quick sort algorithm
//function take the start and end pointers and returns the pivot element
//it works in the pivot method of quick sort
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);


// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
