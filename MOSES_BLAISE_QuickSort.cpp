#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "MOSES_BLAISE_InputFileGenerator.cpp"
using namespace std;

int partition(vector<float> &vals , int start, int end){
    //chooses a pivot index
    int pivotInd = start+(end-start)/2;
    //makes the pivot the value in vals at the pivot index 
    float pivot = vals[pivotInd];
    int i = start;
    int j = end;
    //while i and j have not crossed 
    while(i <= j){
       // iterates i right through vals until a value greater or equal to pivot is found
        while(vals[i] < pivot){
            i++;
        }
        //iterates j left throuhg vals until a value less or equal to the pivot is found
        while(vals[j] > pivot){
            j--;
        }
        //swaps val at index i with val at index j if i and j cross
        if(i <= j){
            float temp = vals[i];
            vals[i] = vals[j];
            vals[j] = temp;
            //increments i by 1 and decrements j by one to account for the swap
            i++;
            j--;
        }
    }
    //returns i to serve as the partition value
    return i;
}
void QuickSort(vector<float> &vals, int start, int end){
    //if the start is a high value than the end then the sort has completed
    if(start>=end)
        return;
    // use partition method to find the partition value of the vector
    int part = partition(vals, start, end);
    //recursively QuickSort the values left and right of the partition 
    QuickSort( vals ,start, part-1);
    QuickSort( vals, part, end); 
}
string SortTimer(vector<float> &vals, double &runtime){
    clock_t start, finish;
    //get start time
    start = clock();
    //run sort 
    QuickSort(vals,0,vals.size()-1);
    //get end time
    finish = clock();
    //calculate the runtime
    runtime = double(finish-start)/double(CLOCKS_PER_SEC);
    //format runtime for runtime file
    stringstream ss;
    ss << vals.size();
    ss << "    ";
    ss << setprecision(0)<< scientific << runtime;
    ss << endl;
    //return string to be added to file.
    return ss.str();
}
string Avg(vector<double> &runtimes, int inputSize){
   stringstream ss;
   //calculate average of all runtimes contained in vector
   double avg = 0;
   for(int i = 0;i< runtimes.size();i++){
        avg += runtimes[i];
   }
   avg /= runtimes.size();
   ss << inputSize;
   ss << "    ";
   ss << setprecision(0)<< scientific << avg;
   ss <<endl;

   return ss.str();
}
int main(int argc, char **argv){
if(argc < 3){
    //generate input files
MakeInputFiles(10);
MakeInputFiles(100);
MakeInputFiles(1000);

//create/open runtime file
 fstream rt;
 rt.open("MOSES_BLAISE_executionTime",fstream::out);
//create/open avg runtime file
fstream avgRt;
avgRt.open("MOSES_BLAISE_averageExecutionTime",fstream::out);
stringstream ss;
 //double to hold runtime
 double runtime;
 //vectors to store runtimes for calculating averages.
 vector<double> runtimes;

//looping through all input files
 for(int i = 1 ; i <= 75; i++){
    ss << "input";
    ss << i;
    ss << ".txt";
    vector<float> vals;
    //read input file vals into vals vector
    FileToArr(ss.str(),vals);
    //write return value of SortTimer to runtime file
    rt << SortTimer(vals,runtime);
    //push runtime to runtimes vecor for calculating average later
    runtimes.push_back(runtime);
    
    //formatting output file names
    ss.str("");
    ss << "output";
    ss << i;
    ss << ".txt";
    //writing output file
    makeOutputFile(vals,ss.str());
    ss.str("");
    
    // for every 25th iteration calculate the average of input size and clears the runtimes vector
    if( i == 25 || i==50 || i==75){
        int entries;
        if(i == 25)
        entries = 10;
        else if(i == 50)
        entries = 100;
        else
        entries = 1000;

        avgRt << Avg(runtimes,entries);
        runtimes.clear();
    }
 }
 //close filestreams
 rt.close();
 avgRt.close();
}
else{
 //create/open runtime file
 fstream rt;
 rt.open("MOSES_BLAISE_executionTime",fstream::out);
 //double to store runtime
 double runtime;

//read input file into vector
    vector<float> vals;
    FileToArr(argv[1],vals);
//call sortTimer to sort and return runtime, which is wrote to runtimes file.
    rt << SortTimer(vals,runtime);
//write output file
     makeOutputFile(vals, argv[2]);
 //close filestream
 rt.close();
}
}
