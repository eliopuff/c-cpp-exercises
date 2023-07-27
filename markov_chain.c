#include "markov_chain.h"

Node* add_to_database (MarkovChain *markov_chain, void *data_ptr)
{
  Node* cur = get_node_from_database (markov_chain, data_ptr);

  if (cur)
    {
      return cur;
    }
  MarkovNode* new = malloc (sizeof(MarkovNode));
  if (!new)
  {
    return NULL;
  }
  void* new_data = markov_chain->copy_func(data_ptr);
  if (!new_data)
  {
    return NULL;
  }
  *new = (MarkovNode){new_data, NULL,
                      0, false, 0, 1};
  if (add(markov_chain->database, new))
  {
    return NULL;
  }
  return markov_chain->database->last;

}



Node* get_node_from_database (MarkovChain *markov_chain, void *data_ptr)
{
  Node* cur = markov_chain->database->first;
  while (cur)
  {
    if (markov_chain->comp_func(cur->data->data, data_ptr) == 0)
    {
      cur->data->appearances++;
      return cur;
    }
    cur = cur->next;
  }
  return NULL;

}

bool add_node_to_frequencies_list(MarkovNode *first_node, MarkovNode
*secondNode, MarkovChain *markov_chain)
{
  for (int i = 0; i < first_node->list_length; i++)
  {
    if (markov_chain->comp_func(first_node->frequencies_list[i]
    .markov_node->data,
               secondNode->data) == 0)
    {
      first_node->frequencies_list[i].frequency++;
      first_node->frequency_total++;
      return true;
    }
  }
  MarkovNodeFrequency* new_frequency_list = NULL;
  if (first_node->frequencies_list)
  {
    new_frequency_list = realloc(
        first_node->frequencies_list,sizeof
        (MarkovNodeFrequency) * ((first_node->list_length) + 1));
    if (!new_frequency_list)
    {
      return false;
    }
  }
  else
  {
    new_frequency_list = malloc(sizeof
        (MarkovNodeFrequency));
    if (!new_frequency_list)
    {
      return false;
    }
  }

  first_node->frequencies_list = new_frequency_list;

  MarkovNodeFrequency* new_node_frequency = &first_node->frequencies_list[
      first_node->list_length];
  new_node_frequency->markov_node = secondNode;
  new_node_frequency->frequency = 1;
  first_node->list_length++;
  first_node->frequency_total++;
  return true;
}

void free_database (MarkovChain **ptr_chain)
{
  MarkovChain* chain = *ptr_chain;
  Node* node = chain->database->first;
  while (node)
  {
    MarkovNode* markov_node = node->data;
    free(markov_node->frequencies_list);
    markov_node->frequencies_list = NULL;
    chain->free_data(markov_node->data);
    markov_node->data = NULL;
    free(markov_node);
    markov_node = NULL;
    Node* temp = node;
    node = node->next;
    free(temp);
    temp = NULL;
  }
  chain->database->first = NULL;
  chain->database->last = NULL;
  free(chain->database);
  chain->database = NULL;
  free(chain);
  chain = NULL;
  *ptr_chain = NULL;
}

int get_random_number (int max_number)
{
  return rand() % max_number;
}

MarkovNode* get_first_random_node (MarkovChain *markov_chain)
{
  int random_number = 0;
  Node* random_node = NULL;
  bool is_end_of_line = true;
  while (is_end_of_line)
  {
    random_number = get_random_number(markov_chain->database->size);
    Node* first_node = markov_chain->database->first;
    random_node = first_node;
    for (int i = 0; i < random_number; i++)
    {
      random_node = random_node->next;
    }
    if (!(random_node->data->is_last))
    {
      is_end_of_line = false;
    }
  }
  return random_node->data;
}

MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr)
{
  int random_number = get_random_number (state_struct_ptr->frequency_total);
  MarkovNode *cur_node = NULL;
  int cur_sum = 0;
  for (int i = 0; i < state_struct_ptr->list_length; i++)
  {
    cur_sum += (state_struct_ptr->frequencies_list[i].frequency);
    if (random_number < cur_sum)
    {
      cur_node = state_struct_ptr->frequencies_list[i].markov_node;
      break;
    }
  }
  return cur_node;
}


void generate_tweet(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
  bool state_ends = false;
  if (!first_node)
  {
    first_node = get_first_random_node (markov_chain);
  }
  int cur_length = 1;
  MarkovNode *next_node = NULL;
  markov_chain->print_func(first_node->data);
  MarkovNode* cur_node = first_node;
  while (!state_ends)
  {
    if (cur_length == max_length || markov_chain->is_last(cur_node->data))
    {
      break;
    }
    next_node = get_next_random_node(cur_node);
    if (markov_chain->is_last(next_node))
    {
      markov_chain->print_func(next_node->data);
      state_ends = true;
      break;
    }
    cur_length++;
    markov_chain->print_func(next_node->data);
    cur_node = next_node;
  }
}