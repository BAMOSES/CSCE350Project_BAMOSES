QUICKSORT EFFICIENCY ANALYZER

Implemented by Blaise Moses

Welcome to the Quicksort Efficiency Analyzer! I designed this program to perform a sort of an input file containing an unsorted list of float values 
via the Quick Sort algorithm, and calculate the runtime of the sort as well as write the values in ascending order to an output file.

The program has two main modes: 

mode 1: single Quicksort: this function is a single sort of a given input file. The user should place their input file in the directory with the source 
code. The user may choose to either provide an output file to be written to or just specify a name for the output file, and the program will create it if 
it does not already exist. The sorted list of values from the input file will be written to the specified output file, and the runtime of the sort will be 
written to the MOSES_BLAISE_executionTime file.

mode 2: fully automated test: this function will automatically generate 75 input files, 25 each of size 10,100, and 1000 float values ranging from -500 to 500.
These float values will then be sorted using the Quicksort algorithm, and the sorted list of each input will be written to an output file. The runtime of each files respective sort 
will be recorded in the MOSES_BLAISE_executionTime file, and the average runtime of each input size (10,100,1000) will be written to the MOSES_BLAISE_averageExecutionTime file.

The input file naming convention is input<test#>.txt and the output file naming convention is output<test#>.txt with test# being an integer 1-75 corresponding to each of the 75 generated lists of values.

Compilation/Using the Program

To compile type following command in command line:

make 

To run the program in mode 1 type the following command in the command line:
 
./run <YourInputFileName> <YourOutputFileName> 

To run the program in mode 2 type the following command in command line:

./run

To delete the generated input and output files from a mode 2 execution use:

make clean






