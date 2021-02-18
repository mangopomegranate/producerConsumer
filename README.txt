Instructions on Compiling and Running Program
1) add all the files into a single directory
  a. The required files to successfully compile and run the test script are:
	1. main.c
	2. shared.h
	3. input.h
	4. separator.h
	5. plus.h
	6. output.h
2) Once inside the directory with the files above
	a) type in the command line:
      gcc --std=gnu99 -pthread main.c -o line_processor
3) an executable file (named: line_processor) will be created in this directory
  a) Note: an executable "line_processor" already exists in submitted folder
4) To run without redirecting stdin:
	a) type in the command line:
        ./line_processor
	b) the program will accept keyboard input to process
  c) the program will output in the terminal
5) To run with input redirection (ex: for file "input1.txt):
	a) type in the command line:
        ./line_processor < input1.txt
  b) output will be displayed in the terminal
6) To run with output redirection (ex: write into file "output1.txt):
	a) type in the command line:
        ./line_processor > output1.txt
  b) output will be printed in file "output1.txt"
7) To run with input and output redirection (ex: process "input1.txt" and write into file "output1.txt):
  a) type in the command line:
        ./line_processor < input1.txt > output1.txt
  b) input in "input1.txt" will be processed and printed in file "output1.txt"