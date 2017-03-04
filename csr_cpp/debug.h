//
// Created by Jia Li on 3/3/17.
//

#include <iostream>
#include <set>
#include <vector>
#include "CSR.h"
#include "SSSP.h"

#ifndef CSR_CPP_DEBUG_H
#define CSR_CPP_DEBUG_H

using namespace std;

template <typename T>
void printVector(vector<T> v, bool children){
    cout << "[";
    for(auto i = v.begin(); i != v.end(); ++i){
        cout << *i << " ";
    }
    cout << "] ";
    if(!children) cout << endl;
}

template <typename T>
void printSetOfVectors(set<vector<T>> s) {
    cout << "( ";
    for(auto it = s.begin(); it != s.end(); ++it){
        printVector(*it, true);
    }
    cout << ")" <<endl;
}

template <typename T>
void printSet(set<T> v){
    cout << "[";
    for(auto i = v.begin(); i != v.end(); ++i){
        cout << *i << " ";
    }
    cout << "] ";
}


#endif //CSR_CPP_DEBUG_H
