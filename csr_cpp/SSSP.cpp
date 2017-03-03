//
// Created by Jia Li on 3/2/17.
//

#include "SSSP.h"
#include "Worklist.h"

DeltaStep::DeltaStep(CSR* csr, int32_t step) : csr(csr), delta(step) {}

void DeltaStep::run() {
    vector <vector<int32_t>> graph = csr->iterate();

    for(auto vertex = graph.begin(); vertex != graph.end(); ++vertex){
        int32_t cost = vertex->at(2);
        if(cost > delta) heavy.insert(*vertex);
        else light.insert(*vertex);
        csr->setTent(vertex->at(0), INT_MAX);
    }
    csr->setTent(0, 0);

    Worklist worklist = Worklist(csr, delta);
    while(worklist.hasElements()){
        unordered_set<vector<int32_t>> s;
        int32_t i = worklist.getIndex();
        while(!worklist.get(i).empty()){
            unordered_set<tuple> req = match(worklist.get(i), true);
            s.insert(worklist.get(i).begin(), worklist.get(i).end());
            worklist.set(i, unordered_set<int32_t>());
            worklist.relaxNodes(req);
        }
        unordered_set<tuple> req = match(worklist.get(i), false);
        worklist.relaxNodes(req);
    }
    csr->printNodeLabels();
    worklist.printRelaxCount();

}

unordered_set<tuple> DeltaStep::match(unordered_set<int32_t> bucket, bool matchLight) {
    unordered_set<tuple> result;

    unordered_set<vector<int32_t>>::iterator b;
    unordered_set<vector<int32_t>>::iterator e;
    if(matchLight){
        b = light.begin();
        e = light.end();
    } else{
        b = heavy.begin();
        e = heavy.end();
    }

    for(b; b != e; ++b){
        if(bucket.find(b->at(0)) != bucket.end()){
            result.insert(tuple(b->at(1), csr->getTent(b->at(0) + b->at(2))));
        }
    }
    return result;
}

Dijkstra::Dijkstra(CSR* csr) : DeltaStep(csr, 1) {}

void Dijkstra::run() {
    DeltaStep::run();
}

ChaoticRelaxation::ChaoticRelaxation(CSR* csr) : DeltaStep(csr, 10) {}

void ChaoticRelaxation::run() {
    DeltaStep::run();
}
