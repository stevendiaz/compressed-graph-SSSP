#include <cstdint>
#include <climits>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <iostream>

#ifndef CSR_h
#define CSR_h

typedef std::pair<int32_t, long> csrTuple;

using namespace std;

class CSR {
private:
    int32_t size;
    vector<int32_t> value;
    vector<int32_t> IA;
    vector<int32_t> JA;
    map<csrTuple, int32_t> seenNodes;
    vector<long> nodeLabels;
    map<int32_t, set<int32_t>> relaxMap;


    void updateValue(int32_t x, int32_t y, int32_t val);

public:
    CSR (int32_t size);

    int32_t get(int32_t x, int32_t y);
    void put(int32_t x, int32_t y, int32_t val);
    vector<vector<int32_t>> iterate();
    void printNodeLabels();
    int32_t getLargestOutDegree();
    long getTent(int32_t u);
    void setTent(int32_t u, long val);
    void debugInfo();
    bool nodeFullyRelaxed(int32_t node);
    void relaxNode(int32_t src, int32_t dest);
};

#endif