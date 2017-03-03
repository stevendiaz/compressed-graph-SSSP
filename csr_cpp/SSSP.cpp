//
// Created by Jia Li on 3/2/17.
//

#include "SSSP.h"
#include "Worklist.h"


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
    csr.setTent(0, 0);

    Worklist worklist = Worklist(csr, delta);
    worklist.setLight(tempLight);
    worklist.setHeavy(tempHeavy);
    while(worklist.hasElements()){
        set<int32_t> s;
        int32_t i = worklist.getIndex();
        while(!worklist.get(i).empty()){
            set<int32_t> bucket = worklist.get(i);
            set<csrTuple> req = match(bucket, worklist.getLight());
            s.insert(bucket.begin(), bucket.end());
            worklist.put(i, set<int32_t>());
            worklist.relaxNodes(req);
        }

        set<csrTuple> req = match(s, worklist.getHeavy());

//        cout << "Req: ";
//        cout << "[";
//        for(auto i = req.begin(); i != req.end(); ++i){
//            cout << "(" << i->first << ", " << i->second << ")";
//        }
//        cout << "] " << endl;
        worklist.relaxNodes(req);
    }
    csr.printNodeLabels();
    worklist.printRelaxCount();

}

set<csrTuple> DeltaStep::match(set<int32_t> bucket, set<vector<int32_t>> s) {
//    cout << "DeltaStep::match" << endl;
    set<csrTuple> result;

    cout << "bucket: ";
    cout << "[";
    for(auto i = bucket.begin(); i != bucket.end(); ++i){
        cout << *i << " ";
    }
    cout << "] " << endl;

    cout << "match set: ";
    printSetOfVectors(s);

    for(auto edge = s.begin(); edge != s.end(); ++edge){
        if(bucket.find(edge->at(0)) != bucket.end()) {
            csrTuple t;
            if(csr.getTent(edge->at(0)) == INT_MAX)
                t = csrTuple(edge->at(1), csr.getTent(edge->at(0)));
            else t = csrTuple(edge->at(1), csr.getTent(edge->at(0)) + edge->at(2));
            cout << "added: (" <<  t.first << ", " << t.second << ")" << endl;
            result.insert(t);
        }
    }
//    cout << "leaving match" << endl;
    return result;
}

//
//Dijkstra::Dijkstra(CSR csr) : DeltaStep(csr, 1) {}
//
//void Dijkstra::run() {
//    DeltaStep::run();
//}
//
//ChaoticRelaxation::ChaoticRelaxation(CSR csr) : DeltaStep(csr, 10) {}
//
//void ChaoticRelaxation::run() {
//    DeltaStep::run();
//}
