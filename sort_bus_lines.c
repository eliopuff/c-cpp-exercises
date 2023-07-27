#include <stdio.h>
#include "sort_bus_lines.h"

void bubble_sort (BusLine *start, BusLine *end){
  int swap_val;

  do {
    swap_val = 0;
    BusLine swap_temp;
    BusLine *first_pointer = start;
    BusLine *second_pointer = first_pointer + 1;

    while (second_pointer < end) {
      // compare adjacent elements and swap them if necessary
      if (strcmp(first_pointer->name, second_pointer->name) > 0) {
        swap_temp = *first_pointer;
        *first_pointer = *second_pointer;
        *second_pointer = swap_temp;

        swap_val = 1;
      }
      first_pointer++;
      second_pointer++;
    }
  } while (swap_val);
}


void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
  if (start >= (end - 1)){
    return;
  }
  BusLine *pivot = partition(start, end, sort_type);
  quick_sort(start, pivot, sort_type);
  quick_sort(pivot + 1, end, sort_type);
}


BusLine *partition (BusLine *start, BusLine *end, SortType sort_type){
  BusLine *pivot = (end - 1);
  BusLine *pointer1 = (start - 1);

  switch (sort_type){
    case DISTANCE:
      for (BusLine *pointer2 = start; pointer2 < (end - 1); pointer2++){
        if (pointer2->distance <= pivot->distance){
          pointer1++;
          BusLine sort_temp = *pointer1;
          *pointer1 = *pointer2;
          *pointer2 = sort_temp;
        }
      }
      break;
    case DURATION:
      for (BusLine *pointer2 = start; pointer2 < (end - 1); pointer2++){
        if (pointer2->duration <= pivot->duration){
          pointer1++;
          BusLine sort_temp = *pointer1;
          *pointer1 = *pointer2;
          *pointer2 = sort_temp;
        }
      }
      break;


  }

  BusLine sort_temp = *(pointer1+1);
  *(pointer1+1) = *(end - 1);
  *(end - 1) = sort_temp;
  return (pointer1+1);

}