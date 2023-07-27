#include "markov_chain.h"
#define MIN_ARGS 4
#define MAX_ARGS 5
#define MAX_TWEET_LENGTH 20
#define NUM_BASE 10
#define MAX_SENTENCE 1000
#define SEED_ARG 1
#define NUM_TWEETS_ARG 2
#define PATH_ARG 3
#define NUM_WORDS_ARG 4

/* function declarations */

static int file_error(const char *path);
// checks for file errors in path
static bool has_period(const char* word, size_t word_length);
// checks if word is last in sentence
static char* copy_the_word(const char* word);
// copies a word complete with memory copying, returns ptr to new word
static void print_str(const char* word);
// prints the word as part of the tweet.
static bool is_last_word(const char* word);
// checks if word is last in sentence, as per generic coding


static int file_error(const char* path)
{
  FILE *file = fopen(path, "r");
  if (!file)
  {
    printf("Error: file path invalid.\n");
    return true;
  }
  fclose(file);
 return false;
}

static char* copy_the_word (const char* word)
{
  char* cur = malloc(strlen(word)+1);
  memcpy(cur, word,strlen(word)+1);
  return cur;
}

static void print_str(const char* word)
{
  printf("%s ", word);
}


static int fill_database (FILE *fp, int words_to_read, MarkovChain
*markov_chain)
{
  char line_buffer[MAX_SENTENCE];
  int words_read = 0;
  bool limitless_words = false;
  if (!words_to_read)
  {
    limitless_words = true;
    words_to_read++;
  }
  while (fgets(line_buffer, sizeof(line_buffer), fp) && words_read <
  words_to_read)
  {
    Node *prev_word_node = NULL;
    char *word = strtok(line_buffer, " \n\r");
    while (word && words_read <
                   words_to_read){
      char* cur_word = copy_the_word(word);
      if (!cur_word) { free_database(&markov_chain);
        return 1; }
      Node *new_node = add_to_database(markov_chain, cur_word);
      if (!new_node) { free_database(&markov_chain);
        return 1; }
      if (new_node->data->appearances > 1) { free(cur_word); }
      words_read++;
      if (limitless_words) { words_to_read++; }
      if (prev_word_node) {
        bool add_success = add_node_to_frequencies_list(prev_word_node->data,
                                          new_node->data, markov_chain);
        if (!add_success){
          free_database(&markov_chain);
          return 1;}
      }
      unsigned const int word_length = strlen(word);
      if (has_period(word, word_length)){
        prev_word_node = NULL;
        new_node->data->is_last = true;}
      else{
        prev_word_node = new_node;
        new_node->data->is_last = false;}
      word = strtok(NULL, " \n\r");
    }
    memset(line_buffer, 0, sizeof(line_buffer));
  }
  return 0;
}

static bool has_period(const char* word, size_t word_length)
{
  if (strcmp(&word[word_length-1], ".") == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

static bool is_last_word(const char* word)
{
  size_t word_length = strlen(word);
  if (strcmp(&word[word_length-1], ".") == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int main(int argc, char *argv[])
{
  if (argc != MIN_ARGS && argc != MAX_ARGS)
    {printf("Usage: program requires seed, number of tweets, path (and number"
           " of words to read).\n");
    return EXIT_FAILURE; }
  if (file_error(argv[PATH_ARG])) {return EXIT_FAILURE;}
  MarkovChain *markov_chain = malloc(sizeof(MarkovChain));
  LinkedList *database = malloc(sizeof(LinkedList));
  if (!markov_chain || !database)
  {
    printf(ALLOCATION_ERROR_MASSAGE);
    free(markov_chain); free(database);
    return EXIT_FAILURE;
  }
  markov_chain->copy_func = (void*)copy_the_word;
  markov_chain->print_func = (void*)print_str;
  markov_chain->free_data = (void*)free;
  markov_chain->is_last = (void*)is_last_word;
  markov_chain->comp_func = (void*)strcmp;
  database->first = NULL;
  database->last = NULL;
  database->size = 0;
  markov_chain->database = database;
  FILE *fp = fopen(argv[PATH_ARG], "r");
  int words_to_read = 0;
  if (argc == MAX_ARGS)
  {
    words_to_read = strtol(argv[NUM_WORDS_ARG], NULL, NUM_BASE);
  }
  int failure_filling_db = fill_database (fp, words_to_read, markov_chain);
  fclose(fp);
  if (failure_filling_db)
  {
    printf(ALLOCATION_ERROR_MASSAGE);
    return EXIT_FAILURE;
  }
  int max_tweets = strtol(argv[NUM_TWEETS_ARG], NULL, NUM_BASE);
  srand(strtol(argv[SEED_ARG], NULL, NUM_BASE));
  for (int i = 1; i <= max_tweets; i++)
  {
    printf("Tweet %d: ", i);
    MarkovNode *first_node = get_first_random_node (markov_chain);
    generate_tweet (markov_chain, first_node, MAX_TWEET_LENGTH);
    printf("\n");
  }
  free_database (&markov_chain);
  return EXIT_SUCCESS;
}
