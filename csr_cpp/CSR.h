#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <climits>

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
};

#endif
