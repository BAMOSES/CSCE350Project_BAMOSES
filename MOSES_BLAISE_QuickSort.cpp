#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <sstream>
#include "/Users/blaisemoses/Desktop/CSCE350Project_MOSES_BLAISE/MOSES_BLAISE_InputFileGenerator.cpp"
using namespace std;

int partition(vector<float> &vals , int start, int end){
    int pivotInd = start+(end-start)/2;
    float pivot = vals[pivotInd];
    int i = start;
    int j = end;
    while(i <= j){
        while(vals[i] < pivot){
            i++;
        }
        while(vals[j] > pivot){
            j--;
        }
        if(i <= j){
            float temp = vals[i];
            vals[i] = vals[j];
            vals[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}
void QuickSort(vector<float> &vals, int start, int end){
    if(start>=end)
        return;
    
    int part = partition(vals, start, end);

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
    FileToArr(ss.str(),vals);
    rt << SortTimer(vals,runtime);
    runtimes.push_back(runtime);
    ss.str("");
    ss << "output";
    ss << i;
    ss << ".txt";
    makeOutputFile(vals,ss.str());
    ss.str("");
    
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