//
// Created by Jia Li on 3/2/17.
//

#include "SSSP.h"
#include "Worklist.h"
#include "debug.h"


DeltaStep::DeltaStep(CSR csr, int32_t step) : csr(csr), delta(step) {}

void DeltaStep::run() {
    vector <vector<int32_t>> graph = csr.iterate();
    set<vector<int32_t>> tempLight;
    set<vector<int32_t>> tempHeavy;

    for(auto vertex = graph.begin(); vertex != graph.end(); ++vertex){
        int32_t cost = vertex->at(2);
        if(cost > delta) {
            tempHeavy.insert(*vertex);
        }
        else {
            tempLight.insert(*vertex);
        }
        csr.setTent(vertex->at(0), INT_MAX);
    }
    csr.setTent(1, 0);

    Worklist worklist = Worklist(csr, delta);
    worklist.setLight(tempLight);
    worklist.setHeavy(tempHeavy);
    while(worklist.hasElements()){
        set<int32_t> s;
        long i = worklist.getIndex();
        while(!worklist.get(i).empty()){
            set<int32_t> bucket = worklist.get(i);
            set<csrTuple> req = worklist.match(bucket, worklist.getLight());
            s.insert(bucket.begin(), bucket.end());
            worklist.put(i, set<int32_t>());
            worklist.relaxNodes(req);
        }
        set<csrTuple> req = worklist.match(s, worklist.getHeavy());
      //   cout << "Req: ";
      //   cout << "[";
      //   for(auto i = req.begin(); i != req.end(); ++i){
      //      cout << "(" << i->first << ", " << i->second << ")";
      //   }
      // cout << "] " << endl;
        worklist.relaxNodes(req);
    }
    worklist.csr.printNodeLabels();
    worklist.printRelaxCount();

}


// Dijkstra::Dijkstra(CSR csr) : DeltaStep(csr, 1) {}

// void Dijkstra::run() {
//     DeltaStep::run();
// }

// ChaoticRelaxation::ChaoticRelaxation(CSR csr) : DeltaStep(csr, 10) {}

// void ChaoticRelaxation::run() {
//     DeltaStep::run();
// }