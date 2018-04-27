//
//  main.cpp
//  lal
//
//  Created by Kevin Shi on 2018/4/25.
//  Copyright © 2018 Kevin Shi. All rights reserved.
//

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

const int row_size = 30;
const int col_size = 30;

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

void lalStaticMatrixAdd(const int iterations, lal::matrix<double, row_size, col_size> mat, vector<long>& runtime){
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; i++){
        mat+=mat;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    runtime.push_back(duration.count());
    return ;
}

void lalTest1Wrapper(const int iterations, lal::matrix<double, row_size, col_size> testMatrix){
    vector<long> runtime;
    for(int i = 1; i <= iterations; i++){
        lalStaticMatrixAdd(10*i, testMatrix, runtime);
    }
    
    ofstream csvfile;
    csvfile.open("lalTest2.csv");
    int counter = 1;
    for(const auto& time:runtime){
        csvfile<<counter*10<<","<<time<<endl;
        counter++;
    }
    csvfile.close();
}

void eigenStaticMatrixAdd(const int iterations, MatrixXf mat, vector<long>& runtime){
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; i++){
        mat+=mat;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    runtime.push_back(duration.count());
    return ;
}

void eigenTest1Wrapper(const int iterations, MatrixXf mat){
    vector<long> runtime;
    for(int i = 1; i <= iterations; i++){
        eigenStaticMatrixAdd(10*i, mat, runtime);
    }
    ofstream csvfile;
    csvfile.open("eigenTest2.csv");
    int counter = 1;
    for(const auto& time:runtime){
        csvfile<<counter*10<<","<<time<<endl;
        counter++;
    }
    csvfile.close();
}

int main(int argc, const char * argv[]) {
    vector<double> test1 = loadMatrixFromFile("Matrix_30_30.txt");
    array<double, row_size*col_size> arr;
    copy_n(test1.begin(), row_size*col_size, arr.begin());
    lal::matrix<double, row_size, col_size> lalTestMatrix1(arr);
    
    lalTest1Wrapper(50, lalTestMatrix1);
    
     MatrixXf eigenTestMatrix1(row_size,col_size);
     
     for(int i = 0; i < row_size; i++){
         for(int j = 0; j < col_size; j++){
             eigenTestMatrix1(i,j) = test1[i*row_size+j];
         }
     }
     
     eigenTest1Wrapper(50, eigenTestMatrix1);
    
    return 0;
}
