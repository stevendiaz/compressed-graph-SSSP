//
// Created by Jia Li on 3/2/17.
//

#ifndef CSR_CPP_WORKLIST_H
#define CSR_CPP_WORKLIST_H


#include <cstdint>
#include <set>
#include <cmath>
#include <algorithm>
#include "CSR.h"
#include "SSSP.h"
#include "debug.h"

class Worklist {
private:
    int32_t delta;
    int32_t relaxCount;
    map<long, set<int32_t>> buckets;
    set<vector<int32_t>> heavy;
    set<vector<int32_t>> light;

    void relax(int32_t e0, long e1);
public:
    CSR csr;
    Worklist(CSR graph, int32_t delta);
    bool hasElements();
    long getIndex();
    set<int32_t> get(long i);
    void put(long i, set<int32_t> nodes);
    void relaxNodes(set<csrTuple> req);
    void printRelaxCount();
    set<vector<int32_t>> getLight();
    void setLight(set<vector<int32_t>> s);
    set<vector<int32_t>> getHeavy();
    void setHeavy(set<vector<int32_t>> s);
    set<csrTuple> match(set<int32_t> bucket, set<vector<int32_t>> s);

};


#endif //CSR_CPP_WORKLIST_H