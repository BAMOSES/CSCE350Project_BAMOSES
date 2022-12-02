
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <random>
#include <sstream>
using namespace std;

void MakeInputFiles(int inputSize){
    stringstream ss;
    random_device random;
    mt19937 generate(random());
    uniform_real_distribution<float> range(-500.0,500.0);
    int count;
    if(inputSize == 10)
        count=1;
    else if(inputSize == 100)
        count = 26; 
     else
        count = 51;
    for( int i = count ; i < (count+25); i++){
       ss<< "input";
       ss << i;
       fstream stream;
       stream.open(ss.str()+".txt",fstream::out);
        ss.str("");
        for(int j = 0; j < inputSize;j++){
            stream << range(generate)<< fixed<< setprecision(5) <<" ";
        }
        stream.close();
    }
    return;
}
void FileToArr(string filename, vector<float> &vals){
    fstream stream;
    stream.open(filename,fstream::in);
    if(!stream){
        cout << "failed to open file";
        return;
    }
    string line;
    float val;
    getline(stream, line);
    stringstream ss(line);
    while(ss >> val){
        vals.push_back(val);
    } 
    return;
}
void makeOutputFile(vector<float> vals, string filename){

    fstream stream;
    stream.open(filename,fstream::out);
    
    for(int i =0 ; i < vals.size(); i++){
        stream <<fixed<< setprecision(5) << vals[i] << " ";
    }
    stream.close();
    return;
}

