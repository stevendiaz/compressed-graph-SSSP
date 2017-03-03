//
// Created by Jia Li on 3/2/17.
//

#include "SSSP.h"
#include "Worklist.h"

DeltaStep::DeltaStep(CSR csr, int32_t step) : csr(csr), delta(step) {}

void DeltaStep::run() {
    vector <vector<int32_t>> graph = csr.iterate();

    for(auto vertex = graph.begin(); vertex != graph.end(); ++vertex){
        int32_t cost = vertex->at(2);
        if(cost > delta) heavy.insert(*vertex);
        else light.insert(*vertex);
        csr.setTent(vertex->at(0), INT_MAX);
    }
    csr.setTent(0, 0);

    Worklist worklist = Worklist(csr, delta);
    while(worklist.hasElements()){
        set<int32_t> s;
        int32_t i = worklist.getIndex();
        cout << "inner while" << endl;
        while(!worklist.get(i).empty()){
            set<int32_t> bucket = worklist.get(i);
            set<csrTuple> req = match(bucket, true);
            s.insert(bucket.begin(), bucket.end());
            worklist.put(i, set<int32_t>());
            worklist.relaxNodes(req);
            cout << "thru" << endl;
        }
        set<csrTuple> req = match(worklist.get(i), false);
        worklist.relaxNodes(req);
    }
    csr.printNodeLabels();
    worklist.printRelaxCount();

}

set<csrTuple> DeltaStep::match(set<int32_t> bucket, bool matchLight) {
    cout << "DeltaStep::match" << endl;
    set<csrTuple> result;

    set<vector<int32_t>>::iterator b;
    set<vector<int32_t>>::iterator e;

    cout << "Set iters" << endl;
    if(matchLight){
        b = light.begin();
        e = light.end();
    } else{
        b = heavy.begin();
        e = heavy.end();
    }

    cout << "for loop" << endl;
    for(b; b != e; ++b){
        if(bucket.find(b->at(0)) != bucket.end()){
            /* FIX THIS!!! potential of overflowing */
            cout << "insert" << endl;
            result.insert(csrTuple(b->at(1), csr.getTent(b->at(0) + b->at(2))));
            cout << "insert completed" << endl;
        }
    }
    cout << "leaving match" << endl;
    return result;
}

Dijkstra::Dijkstra(CSR csr) : DeltaStep(csr, 1) {}

void Dijkstra::run() {
    DeltaStep::run();
}

ChaoticRelaxation::ChaoticRelaxation(CSR csr) : DeltaStep(csr, 10) {}

void ChaoticRelaxation::run() {
    DeltaStep::run();
}
