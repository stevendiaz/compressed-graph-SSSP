//
// Created by Jia Li on 3/2/17.
//

#ifndef CSR_CPP_SSSP_H
#define CSR_CPP_SSSP_H


#include <unordered_set>
#include "CSR.h"

class DeltaStep {
protected:
    CSR* csr;
    int32_t deltaStep;
    int32_t relaxCount;
    unordered_set<vector<int32_t>> heavy;
    unordered_set<vector<int32_t>> light;

public:
    DeltaStep();
    DeltaStep(CSR* csr, int32_t step);
    void run();
};

class Dijkstra : DeltaStep {
public:
    Dijkstra(CSR* csr);
};

class ChaoticRelaxation : DeltaStep {
private:

public:
    ChaoticRelaxation(CSR* csr);
};


#endif //CSR_CPP_SSSP_H
