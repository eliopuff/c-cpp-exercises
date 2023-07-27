//#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define INPUT_LENGTH 60
#define MAX_DISTANCE 1000
#define MIN_DISTANCE 0
#define MAX_DURATION 100
#define MIN_DURATION 10

// HEADERS FOR FUNCTIONS
int irrelevant_command(char *arg);
void do_tests(BusLine *bus_info, BusLine *original_info, size_t input_number);
int is_number_or_letter(const char input[]);
size_t get_input_number();
int valid_type_info(char line_name[], int distance, int duration);
BusLine *get_bus_info(size_t num_input);
void print_sorted(BusLine *sorted_arr, size_t length);
int main (int argc, char *argv[]);






int irrelevant_command(char *arg)
//checks if the argument put through is one that works with our program
{
  if (strcmp(arg, "by_duration") && strcmp(arg, "by_distance") && strcmp
  (arg, "by_name") && strcmp(arg, "test"))
  {
    return 1;
  }
  else {
    return 0;
  }
}

void do_tests(BusLine *bus_info, BusLine *original_info, size_t input_number)
{
  //carried out the tests after each sort, checks the sorts worked
  BusLine *start = bus_info;
  BusLine *end = bus_info + input_number;
  BusLine *orig_start = original_info; //for is_equal to check info retained
  BusLine *orig_end = original_info + input_number;

  quick_sort(start, end, DISTANCE);
  if (is_sorted_by_distance(start, end)){
    printf("TEST 1 PASSED: sorted by distance.\n");
  }
  else {
    printf("TEST 1 FAILED: not sorted by distance.\n");
  }

  if (is_equal(start, end, orig_start, orig_end)){
    printf("TEST 2 PASSED: bus list retained all info.\n");
  }
  else {
    printf("TEST 2 FAILED: bus list altered after sort.\n");
  }
  quick_sort(start, end, DURATION);
  if (is_sorted_by_duration(start, end)){
    printf("TEST 3 PASSED: sorted by duration.\n");
  }
  else {
    printf("TEST 3 FAILED: not sorted by duration.\n");
  }
  if (is_equal(start, end, orig_start, orig_end)){
    printf("TEST 4 PASSED: bus list retained all info.\n");
  }
  else {
    printf("TEST 4 FAILED: bus list altered after sort.\n");
  }
  bubble_sort (start, end);
  if (is_sorted_by_name(start, end)){
    printf("TEST 5 PASSED: sorted by name.\n");
  }
  else{
    printf("TEST 5 FAILED: not sorted by name.\n");
  }
  if (is_equal(start, end, orig_start, orig_end)){
    printf("TEST 6 PASSED: bus list retained all info.\n");
  }
  else {
    printf("TEST 6 FAILED: bus list altered after sort.\n");
  }
}


int is_number_or_letter(const char input[]){
  //for a specific input that may contain numbers or lowercase letters, this
  // function checks that input by looping through the string
  for (int i = 0; input[i] != '\0'; i++)
  {
    if (!(isdigit(input[i])) && !(islower(input[i])))
    {
      return 0;
    }
  }
  return 1;
}


size_t get_input_number(){
  // function gets the number of buslines that are to be entered, checks input
  char input[INPUT_LENGTH];
  size_t number;
  while (1){
    printf("Enter number of lines. Then enter\n");
    fgets(input, INPUT_LENGTH, stdin);
    if (!sscanf(input, "%zu", &number))
    {
      printf ("ERROR: number of lines must be positive integer.\n");
    }
    if (number > 0){
      break;
    }
    else{
      printf("ERROR: number of lines must be positive integer.\n");
    }
  }
  return number;

}



int valid_type_info(char line_name[], int distance, int duration){
  // this function checks the type of bus info entered is valid for our
  // program to process
  if (!is_number_or_letter(line_name)){
    printf("ERROR: bus name should contain only digits and small"
                  " chars.\n");
    return 0;
  }
  else if (distance > MAX_DISTANCE || distance < MIN_DISTANCE){
    printf("ERROR: distance should be non-negative int up to 1000.\n");
    return 0;
  }
  else if (duration > MAX_DURATION || duration < MIN_DURATION){
    printf("ERROR: duration should be an integer between 10"
                   " and 100.\n");
    return 0;
  }
  else{
    return 1;
  }
}


BusLine *get_bus_info(size_t num_input){
  //this function receives all the input data from the user, and adds each
  // valid bus entry to the dynamic array of BusLine structs. if an error is
  // raised, a relevant error message is printed.
  int i = 0;
  int distance, duration;
  char line_name[NAME_LEN];
  BusLine *bus_data = malloc(num_input * sizeof(BusLine));
  if (bus_data == NULL){
    return bus_data;
  }
  while (i < (int)num_input){
    char cur_bus_line[INPUT_LENGTH];
    printf("Enter line info. Then enter\n");
    fgets(cur_bus_line, INPUT_LENGTH, stdin);
    if (!sscanf(cur_bus_line, "%[^,],%d,%d", line_name, &distance,
           &duration)){
      printf("ERROR: problem reading input.\n");
      continue;
    }

    if (valid_type_info(line_name, distance, duration)){
        strcpy(bus_data[i].name, line_name);
        bus_data[i].distance = distance;
        bus_data[i].duration = duration;
        i++;
      }
    }
    return bus_data;

  }


void print_sorted(BusLine *sorted_arr, size_t length){
  int i = 0;
  BusLine *cur = sorted_arr;

  while (i < (int)length)
  {
    printf ("%s,%d,%d\n", cur->name, cur->distance,
            cur->duration);
    cur++;
    i++;
  }
}

int main (int argc, char *argv[])
// our main function, where arg is treated and the program runs
{
  if ((argc != 2) || irrelevant_command(argv[1]))
  {
    printf("USAGE: you may enter a single argument - by_duration,"
                   " by_distance, by_name or test.\n");
    return EXIT_FAILURE;
  }

  size_t input_number = get_input_number();
  BusLine *bus_info = get_bus_info (input_number);
  if (bus_info == NULL){
    //our malloc had failed! return error
    return EXIT_FAILURE;
  }
  if (strcmp(argv[1], "by_name") == 0){
    bubble_sort(bus_info, bus_info + input_number);
  }
  else if (strcmp(argv[1], "by_distance") == 0){
    quick_sort(bus_info, bus_info + input_number, DISTANCE);
  }
  else if (strcmp(argv[1], "by_duration") == 0){
    quick_sort(bus_info, bus_info + input_number, DURATION);
  }
  else if (strcmp(argv[1], "test") == 0){
    BusLine *bus_info_copy = malloc(input_number * sizeof(BusLine));
    if (bus_info_copy == NULL){
      //our malloc had failed! return error
      return EXIT_FAILURE;}
    memcpy(bus_info_copy, bus_info,
           input_number * sizeof(BusLine));
    do_tests(bus_info_copy, bus_info, input_number);
    free(bus_info);
    free(bus_info_copy);
    return EXIT_SUCCESS;
  }
  print_sorted(bus_info, input_number);
  free(bus_info);

  return EXIT_SUCCESS;
}
