//
// Created by Jia Li on 3/2/17.
//

#ifndef CSR_CPP_SSSP_H
#define CSR_CPP_SSSP_H

#include <set>
#include <climits>
#include "util.h"
#include "CSR.h"


class DeltaStep {
protected:
    CSR csr;
    int32_t delta;
    int seed;
    set<vector<int32_t>> heavy;
    set<vector<int32_t>> light;

public:
    DeltaStep();
    DeltaStep(CSR csr, int32_t step, int seed);
    void run(bool printNLabels, bool printRelaxCount);
};


#endif //CSR_CPP_SSSP_H
