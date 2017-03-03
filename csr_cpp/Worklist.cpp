//
// Created by Jia Li on 3/2/17.
//

#include "Worklist.h"

Worklist::Worklist(CSR graph, int32_t delta) : csr(graph), delta(delta), relaxCount(0) {
    buckets = map<int32_t, set<int32_t>>();
    vector<vector<int32_t>> vals = graph.iterate();
    int32_t w = 0;

    for(auto it = vals.begin(); it != vals.end(); ++it){
        w = it->at(0);
        int32_t i = floor(graph.getTent(w)/delta);
        cout  << "i is " << i << endl;

        if(buckets.find(i) == buckets.end()){
            buckets[i] = set<int32_t>();
            buckets[i].insert(w);
        } else buckets[i].insert(w);
    }
}

bool Worklist::hasElements() {
    for(auto it = buckets.begin(); it != buckets.end(); ++it){
        if(it->second.size() != 0) return true;
    }
    return false;
}

int32_t Worklist::getIndex() {

    cout << "Worklist::getIndex()" <<endl;
    for(auto it = buckets.begin(); it != buckets.end(); ++it)
        if(it->second.size() > 0) return it->first;

    return -1;
}

set<int32_t> Worklist::get(int32_t i) {
    return buckets[i];
}

void Worklist::put(int32_t i, set<int32_t> nodes) {
    cout << "WL::put" << endl;
    buckets[i] = nodes;
}

void Worklist::relax(int32_t w, int32_t d) {
    cout << "RELAX" << endl;
    ++relaxCount;
    int32_t tentCost = csr.getTent(w);
    if(d < tentCost){
        csr.setTent(w, d);
        int32_t i = floor(tentCost/delta);
        if(buckets[i].find(w) != buckets[i].end()) buckets[i].erase(w);
        int32_t newInd = floor(d/delta);
        if(buckets.find(newInd) == buckets.end())
            buckets[newInd] = set<int32_t>({w});
        else buckets[newInd].insert(w);
    }
}

void Worklist::relaxNodes(set<csrTuple> req) {
    cout << "Worklist::relaxNodes()" <<endl;
    vector<csrTuple> reqVector(req.begin(), req.end());
    random_shuffle(reqVector.begin(), reqVector.end());

    for (auto it = reqVector.begin(); it != reqVector.end(); ++it) {
        relax(it->first, it->second);
    }
}

void Worklist::printRelaxCount() {
    cout << "Relaxations: " << relaxCount << endl;
}
