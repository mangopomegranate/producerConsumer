/*
* Citation: 6_5_prod_cons_pipeline.c
* Citation: 6_4_prod_cons_unbounded.c
*/

#include "shared.h"

/*
Get the next item from buffer 3
*/
char* get_buff_3()
{
  // Lock the mutex before checking if the buffer has data
  pthread_mutex_lock(&mutex_3);
  while (count_3 == 0)
  {
    // Buffer is empty. Wait for the producer to signal that the buffer has data
    pthread_cond_wait(&full_3, &mutex_3);
  }
  char* item = buffer_3[con_idx_3];
  // Increment the index from which the item will be picked up
  con_idx_3 = con_idx_3 + 1;
  count_3--;
  // Signal to the producer that the buffer has space
  //pthread_cond_signal(&empty_3);
  // Unlock the mutex
  pthread_mutex_unlock(&mutex_3);
  // Return the item
  return item; 
}



/*
* Function Prints 80 characters to stdout
*/
void printEighty(void)
{
  int outLen = strlen(outLine);
  //printf("OUTLINE_B: %s\n", outLine);
  //printf("OUTLEN_B: %d\n", outLen);
  while (outLen >= 79)
  {
    int k = 0;
    //printf("\n");
    for (int c = 0; c < 80;c++)
    {
      printf("%c", outLine[c]);
      k = c;
    }
    printf("\n");
    memmove(&outLine[0], &outLine[k + 1], strlen(outLine) - (k+1));
    outLen = outLen - 80;
    outLine[outLen] = '\0';
    //printf("OUTLINE_A: %s\n", outLine);
    //printf("OUTLEN_A: %d\n", outLen);
  }
  return;
}

/*
* gets each line from buffer_3
* print 80 characters
*/
void *outputEighty(void *args)
{
  // Get item from buffer_3
  // Continue consuming until the END_MARKER is seen
  while (strcmp(tempLine, END_MARKER) != 0)
  {
    strcpy(tempLine, get_buff_3());
    strcat(outLine, tempLine);
    // print 80 charcters to stdout
    printEighty();
  }
  // 
  return NULL;
}