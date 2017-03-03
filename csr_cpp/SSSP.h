//
// Created by Jia Li on 3/2/17.
//

#ifndef CSR_CPP_SSSP_H
#define CSR_CPP_SSSP_H


#include <unordered_set>
#include <climits>
#include "CSR.h"


class DeltaStep {
protected:
    CSR* csr;
    int32_t delta;
    unordered_set<vector<int32_t>> heavy;
    unordered_set<vector<int32_t>> light;

public:
    DeltaStep();
    DeltaStep(CSR* csr, int32_t step);
    void run();
    unordered_set<csrTuple> match(unordered_set<int32_t> bucket, bool matchLight);
};

class Dijkstra : DeltaStep {
public:
    Dijkstra(CSR* csr);
    void run();
};

class ChaoticRelaxation : DeltaStep {
public:
    ChaoticRelaxation(CSR* csr);
    void run();
};


#endif //CSR_CPP_SSSP_H
