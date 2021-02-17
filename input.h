#include "shared.h"


/*
* citation: 6_5_prod_cons_pipeline.c
* Put an item in buffer_1
*/

void put_buff_1(char* item){
  // Lock the mutex before putting the item in the buffer
  pthread_mutex_lock(&mutex_1);
  // Put the item in the buffer
  buffer_1[prod_idx_1] = strdup(item);
  // Increment the index where the next item will be put.
  prod_idx_1 = prod_idx_1 + 1;
  count_1++;
  // Signal to the consumer that the buffer is no longer empty
  pthread_cond_signal(&full_1);
  // Unlock the mutex
  pthread_mutex_unlock(&mutex_1);

}

/*
* citation: 6_5_prod_cons_pipeline.c
* Function that the input thread will run.
* Get input from the user.
* Put item in the shared buffer
*/
void *get_input(void *args)
{
  // From handout:
  // The input for the program will never have more than 49 lines before the STOP-Processing line
  // i.e. input is assumed to end at line 50
  for (int i = 0; i < NUM_ITEMS; i++)
  {
    // place next line in temLine
    fgets(tempLine, CHAR, stdin);
    // check if line has STOP signals
    if (strcmp(tempLine, END_MARKER) == 0)
    {
      put_buff_1(END_MARKER);
      break;
    } else 
    {
      // place line in buffer
      put_buff_1(tempLine);
    }
  }
  
  /*
  *TEST:Checks if input correctly placed in buffer
  */
  /*
  printf("\nprod_id: %d\n", prod_idx_1);
  //printf("buffer = %s\n", buffer_1[0]);
  
  for (int j=0; buffer_1[j]; j++)
  {
    printf("j = %d\n", j);
    printf("buffer = %s\n", buffer_1[j]);
  }
  */
  return NULL;
}