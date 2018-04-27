#include <iostream>
#include <Eigen/Dense>
#include "include/matrix.hpp"
#include "include/dmatrix.hpp"
#include <array>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;
using namespace Eigen;
using namespace chrono;

//const size_t row_size = 30;
//const size_t col_size = 30;

vector<double> loadMatrixFromFile(string filename){
    
    vector<double> result;
    ifstream reader;
    reader.open(filename);
    
    while(!reader.eof()){
        string line;
        getline(reader, line);
        
        stringstream stream(line);
        while(!stream.eof()){
            double temp;
            stream>>temp;
            result.push_back(temp);
        }
    }
    reader.close();
    return result;
}

void lalStaticMatrixAdd(const int iterations, lal::dynamic_matrix<double> mat, vector<long>& runtime, vector<double>& toBeInserted){
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; i++){
        mat.insert_row(0, toBeInserted);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    runtime.push_back(duration.count());
    return ;
}

void lalTest1Wrapper(const int iterations, lal::dynamic_matrix<double> testMatrix, vector<double>& toBeInserted){
    vector<long> runtime;
    for(int i = 1; i <= iterations; i++){
        lalStaticMatrixAdd(10*i, testMatrix, runtime, toBeInserted);
    }
    
    ofstream csvfile;
    csvfile.open("lalTest6.csv");
    int counter = 1;
    for(const auto& time:runtime){
        csvfile<<counter*10<<","<<time<<endl;
        counter++;
    }
    csvfile.close();
}

void eigenStaticMatrixAdd(const int iterations, MatrixXd mat, vector<long>& runtime, MatrixXd toBeInserted){
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; i++){
        MatrixXd D(mat.rows()+toBeInserted.rows(), mat.cols());
        D << mat,
        toBeInserted;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    runtime.push_back(duration.count());
    return ;
}

void eigenTest1Wrapper(const int iterations, MatrixXd mat, MatrixXd toBeInserted){
    vector<long> runtime;
    for(int i = 1; i <= iterations; i++){
        eigenStaticMatrixAdd(i, mat, runtime, toBeInserted);
    }
    ofstream csvfile;
    csvfile.open("eigenTest6.csv");
    int counter = 1;
    for(const auto& time:runtime){
        csvfile<<counter*10<<","<<time<<endl;
        counter++;
    }
    csvfile.close();
}

int main(int argc, const char * argv[]) {
    vector<double> test1 = loadMatrixFromFile("Matrix_10_20.txt");
    //array<double, row_size*col_size> arr;
    //copy_n(test1.begin(), row_size*col_size, arr.begin());
    
    lal::dynamic_matrix<double> lalTestMatrix1(1, test1.size(), 0);
    
    
    lalTest1Wrapper(50, lalTestMatrix1, test1);
    
    
    MatrixXd eigenTestMatrix1(1, test1.size());
    
    MatrixXd eigenTobeInserted(1, test1.size());
    for(int i = 0; i < test1.size(); i++){
        eigenTestMatrix1(0, i) = test1[i];
        eigenTestMatrix1(0, i) = test1[i];
    }
    
    eigenTest1Wrapper(50, eigenTestMatrix1, eigenTobeInserted);
    
    return 0;
}
