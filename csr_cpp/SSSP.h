//
// Created by Jia Li on 3/2/17.
//

#ifndef CSR_CPP_SSSP_H
#define CSR_CPP_SSSP_H

#include <set>
#include <climits>
#include "CSR.h"
#include "debug.h"


class DeltaStep {
protected:
    CSR csr;
    int32_t delta;
    set<vector<int32_t>> heavy;
    set<vector<int32_t>> light;

public:
    DeltaStep();
    DeltaStep(CSR csr, int32_t step);
    void run();
    set<csrTuple> match(set<int32_t> bucket, set<vector<int32_t>> matchSet);
};

class Dijkstra : DeltaStep {
public:
    Dijkstra(CSR csr);
    void run();
};

class ChaoticRelaxation : DeltaStep {
public:
    ChaoticRelaxation(CSR csr);
    void run();
};


#endif //CSR_CPP_SSSP_H
