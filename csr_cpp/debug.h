//
// Created by Jia Li on 3/3/17.
//

#include <iostream>
#include <cstdint>
#include <set>
#include <vector>
#include <map>

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

//void printBuckets(map<long, set<int32_t>> buckets) {
//    cout << "buckets: ";
//    cout << "{";
//    for(auto i = buckets.begin(); i != buckets.end(); ++i){
//        cout << i->first << ": " ;
//        cout << "(";
//        for(auto it = i->second.begin(); it != i->second.end(); ++it){
//            cout << *it << " ";
//        }
//        cout << ") ";
//    }
//    cout << "}" << endl;
//}
#endif //CSR_CPP_DEBUG_H
