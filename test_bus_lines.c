#include "test_bus_lines.h"
#include <stdio.h>

int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  int arr_len = end - start;
  int i = 0;
  while (i < (arr_len-1)){
    if (start[i].distance > start[i+1].distance){
      return 0;
    }
    i++;
  }
  return 1;
}

int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  int arr_len = end - start;
  int i = 0;
  while (i < (arr_len-1)){
    if (start[i].duration > start[i+1].duration){
      return 0;
    }
    i++;
  }
  return 1;
}


int is_sorted_by_name (BusLine *start, BusLine *end)
{
  int arr_len = end - start;
  int i = 0;
  while (i < arr_len-1){
    int compare = strcmp(start[i].name, start[i+1].name);
    if (compare > 0){
      return 0;
    }
    i++;
  }
  return 1;
}


int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original) {
  int arr_len_sorted = end_sorted - start_sorted;
  int arr_len_original = end_original - start_original;
  if (arr_len_original != arr_len_sorted){
    return 0;
  }
  int eq_count = 0;
  for (int i = 0; i < arr_len_sorted; i++){
    for (int j = 0; j < arr_len_sorted; j++){
      if (strcmp(start_sorted[i].name,start_sorted[j].name) == 0){
        eq_count++;
      }
    }
    if (eq_count != (i + 1))
      {
      return 0;
      }
  }
  return 1;
}