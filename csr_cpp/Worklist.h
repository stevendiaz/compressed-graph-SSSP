//
// Created by Jia Li on 3/2/17.
//

#ifndef CSR_CPP_WORKLIST_H
#define CSR_CPP_WORKLIST_H


#include <cstdint>
#include <unordered_set>
#include "CSR.h"

class Worklist {
private:
    CSR* csr;
    int32_t delta;
    int32_t relaxCount;
    map<int32_t, unordered_set<int32_t>> buckets;

    void relax(int32_t e0, int32_t e1);
public:
    Worklist(CSR* graph, int32_t delta);
    bool hasElements();
    int32_t getIndex();
    unordered_set<int32_t> get(int32_t i);
    void set(int32_t i, unordered_set<int32_t> nodes);
    void relaxNodes(unordered_set<csrTuple> req);
    void printRelaxCount();

};


#endif //CSR_CPP_WORKLIST_H
