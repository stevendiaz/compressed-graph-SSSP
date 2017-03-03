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
        cout << "in while" << endl;
        set<int32_t> s;
        int32_t i = worklist.getIndex();
        while(!worklist.get(i).empty()){
            cout << "inner while" << endl;
            set<csrTuple> req = match(worklist.get(i), true);
            cout << "insert" << endl;
            cout << "size of bucket: " << worklist.get(i).size() << endl;
            // s.insert(worklist.get(i).begin(), worklist.get(i).end());
            
            for(auto it = worklist.get(i).begin(); it != worklist.get(i).end(); ++it){
                cout << *it << endl;
                s.insert(*it);
            }
            cout << "insert complete" << endl;
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
    if(matchLight){
        b = light.begin();
        e = light.end();
    } else{
        b = heavy.begin();
        e = heavy.end();
    }

    for(b; b != e; ++b){
        if(bucket.find(b->at(0)) != bucket.end()){
            /* FIX THIS!!! potential of overflowing */
            result.insert(csrTuple(b->at(1), csr.getTent(b->at(0) + b->at(2))));
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
