#compile program using the command "make compile"
compile:
	g++ -o run MOSES_BLAISE_QuickSort.cpp

#two options for running : 
#option 1:for single test using a given input file and either a given output file or a name of one to be created

#option 2: fully automated test, generating 75 random files, 25 each of size 10,100,and 1000 inputs, and calculating the average runtime of each size.

#for option 1: use command "./run <YourInputFileName> <YourOutputFileName>" in command line
#for option 2: use command "./run" in command line

#delete the generated input and output files
clean:
	find -type f -name 'input*' -delete
	find -type f -name 'output*' -delete
