//
// Created by Jia Li on 3/2/17.
//

#include "SSSP.h"
#include "Worklist.h"


DeltaStep::DeltaStep(CSR *csr, int32_t step) : csr(csr), delta(step) {}

void DeltaStep::run() {
    vector <vector<int32_t>> graph = csr->iterate();
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
        csr->setTent(vertex->at(0), INT_MAX);
    }
    csr->setTent(0, 0);

    Worklist worklist = Worklist(csr, delta);
    worklist.setLight(tempLight);
    worklist.setHeavy(tempHeavy);
    while(worklist.hasElements()){
        set<int32_t> s;
        long i = worklist.getIndex();
        while(!worklist.get(i).empty()){
            set<int32_t> bucket = worklist.get(i);
            cout << "light match!" << endl;
            set<csrTuple> req = match(bucket, worklist.getLight());
            s.insert(bucket.begin(), bucket.end());
            worklist.put(i, set<int32_t>());
            worklist.relaxNodes(req);
            cout << "DeltaStep::run node labels" << endl;
            csr->printNodeLabels();
        }
        cout << "heavy match!" << endl;
        set<csrTuple> req = match(s, worklist.getHeavy());
        worklist.relaxNodes(req);
    }
    csr->printNodeLabels();
    worklist.printRelaxCount();

}

set<csrTuple> DeltaStep::match(set<int32_t> bucket, set<vector<int32_t>> matchSet) {
//    cout << "DeltaStep::match" << endl;
    set<csrTuple> result;
//    csr.printNodeLabels();

//    cout << "bucket: ";
//    printSet(bucket);
//    cout << endl;
//
//    cout << "match set: ";
//    printSetOfVectors(matchSet);

    for(auto edge = matchSet.begin(); edge != matchSet.end(); ++edge){
        if(bucket.find(edge->at(0)) != bucket.end()) {
            csrTuple t(edge->at(1), csr->getTent(edge->at(0)) + edge->at(2));
            result.insert(t);
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
