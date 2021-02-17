/*
* Citation: 6_5_prod_cons_pipeline.c
* Citation: 6_4_prod_cons_unbounded.c
*/

#include "shared.h"

/*
Get the next item from buffer 1
*/
char* get_buff_1()
{
  // Lock the mutex before checking if the buffer has data
  pthread_mutex_lock(&mutex_1);
  while (count_1 == 0)
  {
    // Buffer is empty. Wait for the producer to signal that the buffer has data
    pthread_cond_wait(&full_1, &mutex_1);
  }
  char* item = buffer_1[con_idx_1];
  // Increment the index from which the item will be picked up
  con_idx_1 = con_idx_1 + 1;
  count_1--;
  // Signal to the producer that the buffer has space
  pthread_cond_signal(&empty_1);
  // Unlock the mutex
  pthread_mutex_unlock(&mutex_1);
  // Return the item
  return item; 
}

/*
* Put an item in buffer_2
*/
void put_buff_2(char* item)
{
  // Lock the mutex before putting the item in the buffer
  pthread_mutex_lock(&mutex_2);
  // Put the item in the buffer
  buffer_2[prod_idx_2] = strdup(item);
  // Increment the index where the next item will be put.
  prod_idx_2 = prod_idx_2 + 1;
  count_2++;
  // Signal to the consumer that the buffer is no longer empty
  pthread_cond_signal(&full_2);
  // Unlock the mutex
  pthread_mutex_unlock(&mutex_2);
}

/*
* Function replaces line separater with a space
*/
void swapWithSpace(void)
{
  // get the length of line in buffer
  int tempLen = strlen(tempLine);
  // iterate over every character in line
  for (int k = 0; k < tempLen; k++)
  {
    // find end of line separator
    if (tempLine[k] == '\n')
    {
      tempLine[k] = ' ';
    }
  }
  
  /* 
  FOR TESTS: checks for unreplaced \n in tempLine
  */
  /*
  for (int m = 0; m < tempLen; m++)
  {
    if (tempLine[m] == '\n')
    {
      printf("found\n");
    }
  }
  */
  
  return;
}

/*
* gets each line from buffer_1
* replaces "\n" with " "
* places replaced line in buffer_2
*/
void *separateLine(void *args)
{
  // Get item from buffer_1
  // Continue consuming until the END_MARKER is seen
  while (strcmp(tempLine, END_MARKER) != 0)
  {
    strcpy(tempLine, get_buff_1());
    // don't replace END_MARKER
    if (strcmp(tempLine, END_MARKER) != 0)
    {
      // Process item: place '\n' with ' '
      swapWithSpace();
    }
    // Place Processed item in buffer_2
    put_buff_2(tempLine);
  }
  
  /*
  * TEST: Check buffer_2 is loaded properly
  */
  /*
  for (int j=0; buffer_2[j]; j++)
  {
    printf("j = %d\n", j);
    printf("buffer = %s\n", buffer_2[j]);
  }
  */
  return NULL;
}