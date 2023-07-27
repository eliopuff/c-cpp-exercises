#include <string.h> // For strlen(), strcmp(), strcpy()
#include <stdio.h>
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY (-1)
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20

#define SEED_ARG 1
#define NUM_PATHS_ARG 2
#define NUM_BASE 10
#define ARGS_AMOUNT 3


/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;
    // ladder_to represents the jump of the
    // ladder in case there is one from this square
    int snake_to;  // snake_to represents the jump of the
    // snake in case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

static void* copy_cell(void* data_ptr); // for generic copy data func
static void print_cell(Cell* cell); // for generic print func
static bool is_final_cell(Cell* cell); // for generic is_last func

static bool is_final_cell(Cell* cell)
{
  if (cell->number == BOARD_SIZE)
  {
    return true;
  }
  else
  {
    return false;
  }
}


static void print_cell(Cell* cell)
{
  printf("[%d]", cell->number);
  if (cell->ladder_to > -1)
  {
    printf("-ladder to %d -> ", cell->ladder_to);
  }
  else if (cell-> snake_to > -1)
  {
    printf("-snake to %d -> ", cell->snake_to);
  }
  else if (!is_final_cell(cell))
  {
    printf(" -> ");
  }
}

/** Error handler **/
static int handle_error(char *error_msg, MarkovChain **database)
{
    printf("%s", error_msg);
    if (database != NULL)
    {
        free_database(database);
    }
    return EXIT_FAILURE;
}


static int create_board(Cell *cells[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc(sizeof(Cell));
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++) {
                free(cells[j]);
            }
            handle_error(ALLOCATION_ERROR_MASSAGE,NULL);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        }
        else
        {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database(MarkovChain *markov_chain)
{
    Cell* cells[BOARD_SIZE];
    if(create_board(cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        add_to_database(markov_chain, cells[i]);
    }

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database(markov_chain,cells[i])->data;

        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to,cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain, cells[index_to])
                    ->data;
            add_node_to_frequencies_list (from_node, to_node, markov_chain);
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell*) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database(markov_chain, cells[index_to])
                        ->data;
                add_node_to_frequencies_list (from_node, to_node,
                                              markov_chain);
            }
        }
    }
    // free temp arr
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        free(cells[i]);
    }
    return EXIT_SUCCESS;
}


static void* copy_cell(void* data_ptr)
{
  if (!data_ptr)
  {
    return NULL;
  }

  Cell* new_cell = malloc(sizeof(Cell));
  if (!new_cell)
  {
    return NULL;
  }
  memcpy(new_cell, data_ptr, sizeof(Cell));
  return new_cell;
}


/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
  if (argc != ARGS_AMOUNT) {return EXIT_FAILURE;}
  unsigned int seed = strtol(argv[SEED_ARG], NULL, NUM_BASE);
  srand(seed);
  unsigned int num_paths = strtol(argv[NUM_PATHS_ARG], NULL, NUM_BASE);
  MarkovChain* markov_chain = malloc(sizeof(MarkovChain));
  LinkedList* database = malloc(sizeof(LinkedList));
  if (!markov_chain || !database)
  {
    handle_error(ALLOCATION_ERROR_MASSAGE, &markov_chain);
    free(markov_chain); free(database);
    return EXIT_FAILURE;
  }
  markov_chain->copy_func = (void*)copy_cell;
  markov_chain->print_func = (void*)print_cell;
  markov_chain->free_data = (void*)free;
  markov_chain->is_last = (void*)is_final_cell;
  markov_chain->comp_func = (void*)strcmp;
  database->first = NULL;
  database->last = NULL;
  database->size = 0;
  markov_chain->database = database;
  int failure_filling_database = fill_database(markov_chain);
  if (failure_filling_database)
  {
    handle_error(ALLOCATION_ERROR_MASSAGE, &markov_chain);
    return EXIT_FAILURE;
  }
  MarkovNode* first_node = database->first->data;
  for (unsigned int i = 1; i <= num_paths; i++)
  {
    printf("Random Walk %d: ", i);
    generate_tweet (markov_chain, first_node, MAX_GENERATION_LENGTH);
    printf("\n");
  }
  free_database (&markov_chain);
  return EXIT_SUCCESS;
}
