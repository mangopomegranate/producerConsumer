/*
* we start as one thread that does task of four threads
* Citation: Thread description from assignment handout cs344 winter2021
* 1) Reads in lines of characters from the standard input
* 2) Replaces every line separator in the input by a space
* 3) replaces every pair of plus signs, i.e., "++", by a "^"
* 4) weire this processed data to standard output as lines of exactly 80 characters
*/
#include "shared.h"
#include "input.h"

int main(){
  //srand(time(0));
  pthread_t input_t, output_t;
  // Create the threads
  pthread_create(&input_t, NULL, get_input, NULL);
  
  pthread_join(input_t, NULL);

  return EXIT_SUCCESS;
}