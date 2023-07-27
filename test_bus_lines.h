#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

//test function to make sure buslines are sorted by distance
int is_sorted_by_distance (BusLine *start, BusLine *end);

//test function to make sure buslines are sorted by duration
int is_sorted_by_duration (BusLine *start, BusLine *end);

//test function to make sure buslines are sorted by name
int is_sorted_by_name (BusLine *start, BusLine *end);

//test function to make sure sorting didn't change the contents of the arrays
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);


// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
