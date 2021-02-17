/*
* Citation: 6_5_prod_cons_pipeline.c
* Citation: 6_4_prod_cons_unbounded.c
*/

#include "shared.h"

/*
Get the next item from buffer 2
*/
char* get_buff_2()
{
  // Lock the mutex before checking if the buffer has data
  pthread_mutex_lock(&mutex_2);
  while (count_2 == 0)
  {
    // Buffer is empty. Wait for the producer to signal that the buffer has data
    pthread_cond_wait(&full_2, &mutex_2);
  }
  char* item = buffer_2[con_idx_2];
  // Increment the index from which the item will be picked up
  con_idx_2 = con_idx_2 + 1;
  count_2--;
  // Signal to the producer that the buffer has space
  pthread_cond_signal(&empty_2);
  // Unlock the mutex
  pthread_mutex_unlock(&mutex_2);
  // Return the item
  return item; 
}

/*
* Put an item in buffer_3
*/
void put_buff_3(char* item)
{
  // Lock the mutex before putting the item in the buffer
  pthread_mutex_lock(&mutex_3);
  // Put the item in the buffer
  buffer_3[prod_idx_3] = strdup(item);
  // Increment the index where the next item will be put.
  prod_idx_3 = prod_idx_3 + 1;
  count_3++;
  // Signal to the consumer that the buffer is no longer empty
  pthread_cond_signal(&full_3);
  // Unlock the mutex
  pthread_mutex_unlock(&mutex_3);
}

/*
* Function replaces "++" by "^"
*/
void swapPlus(void)
{
  // get the length of line in buffer
  int tempLen = strlen(tempLine);
  // iterate over every character in line
  for (int k = 0; k < tempLen; k++)
  {
    // find '++'
    if (tempLine[k] == '+' && tempLine[k+1] == '+')
    {
      // replace first '+' with '^'
      tempLine[k] = '^';
      // Citation: https://stackoverflow.com/questions/5457608/how-to-remove-the-character-at-a-given-index-from-a-string-in-c
      // skips over second '+'
      memmove(&tempLine[k+1], &tempLine[k + 2], strlen(tempLine) - (k+1));      
    }
  }
  
  return;
}

/*
* gets each line from buffer_2
* replaces "\n" with " "
* places replaced line in buffer_3
*/
void *replacePlus(void *args)
{
  // Get item from buffer_2
  // Continue consuming until the END_MARKER is seen
  while (strcmp(tempLine, END_MARKER) != 0)
  {
    strcpy(tempLine, get_buff_2());
    // don't replace END_MARKER
    if (strcmp(tempLine, END_MARKER) != 0)
    {
      // Process item: place '\n' with ' '
      swapPlus();
    }
    // Place Processed item in buffer_3
    put_buff_3(tempLine);
  }
  
  /*
  * TEST: Check buffer_3 is loaded properly
  */
  /*
  for (int j=0; buffer_3[j]; j++)
  {
    printf("\nj = %d\n", j);
    printf("\nbuffer = %s\n", buffer_3[j]);
  }
  */
  return NULL;
}