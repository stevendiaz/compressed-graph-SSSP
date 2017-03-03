//
// Created by Jia Li on 3/2/17.
//

#include "SSSP.h"

DeltaStep::DeltaStep(CSR* csr, int32_t step) : csr(csr), deltaStep(step), relaxCount(0) {}

void DeltaStep::run() {
    vector <vector<int32_t>> graph = csr->iterate();

    for(auto it = graph.begin(); it != graph.end(); ++it){
        int32_t cost = it->at(2);
        if(cost > deltaStep) heavy.insert(*it);
        else light.insert(*it);

        csr->setTent(it->at(0), )
    }

}

Dijkstra::Dijkstra(CSR* csr) : DeltaStep(csr, 1) {}

ChaoticRelaxation::ChaoticRelaxation(CSR* csr) : DeltaStep(csr, 10) {}
