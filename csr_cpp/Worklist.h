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
    int32_t delta;
    map<int32_t, unordered_set<int32_t>> buckets;
public:
    Worklist(int32_t delta, CSR graph);
    bool hasElements();
    int32_t getIndex();
    unordered_set<int32_t> get(int32_t i);
    void set(int32_t i, unordered_set<int32_t> nodes);
    void relaxNodes(CSR graph, unordered_set<int32_t> req);

};


#endif //CSR_CPP_WORKLIST_H
