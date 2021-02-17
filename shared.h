/*
Contains constants shared among
threads
*/

/*
Citation: CS344 Winter 2021
Example from Assignment Handout
6_5_prod_cons_pipeline.c
*/

#ifndef shared
#define shared

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// Size of buffers
// Buffer holds 50 lines
#define SIZE 50
// Number of items that will be produced before the END_MARKER
// Note that this number is smaller than the size of the buffer. This means that we can model the buffer as unbounded
// Citation: 6_4_prod_cons_unbounded.c
#define NUM_ITEMS 49
// Special marker used to indicate end of the producer data
#define END_MARKER "STOP\n"
// 1000 characters in each line
// ** Don't know how to use this yet, but need to store each character in line
#define CHAR 1000
// store temporary string
char inputLine[CHAR];
char sepLine[CHAR];
char plusLine[CHAR];
char tempLine[CHAR];
char outLine[CHAR];

/*****Buffer 1*****/
// Buffer, shared resource
// between input and separator
char* buffer_1[SIZE];
// Number of items in the buffer, shared resource
// between input and separator
int count_1 = 0;
// Index where input thread will put the next items
int prod_idx_1 = 0;
// Index where seprator thread will pick up the next item
int con_idx_1 = 0;

// Initialize the mutex
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;

// Initialize the condition variables
pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty_1 = PTHREAD_COND_INITIALIZER;

/*****Buffer 2*****/
// Buffer, shared resource
// between separator and plus sign thread
char* buffer_2[SIZE];
// Number of items in the buffer, shared resource
// between separator and plus sign
int count_2 = 0;
// Index where separator thread will put the next items
int prod_idx_2 = 0;
// Index where plus sign thread will pick up the next item
int con_idx_2 = 0;

// Initialize the mutex
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;

// Initialize the condition variables
pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty_2 = PTHREAD_COND_INITIALIZER;

/*****Buffer 3*****/
// Buffer, shared resource
// between plus sign thread and output thread
char* buffer_3[SIZE];
// Number of items in the buffer, shared resource
// between plus sign and output
int count_3 = 0;
// Index where plus sign thread will put the next items
int prod_idx_3 = 0;
// Index where output thread will pick up the next item
int con_idx_3 = 0;

// Initialize the mutex
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;

// Initialize the condition variables
pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty_3 = PTHREAD_COND_INITIALIZER;
#endif