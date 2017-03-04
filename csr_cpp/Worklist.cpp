//
// Created by Jia Li on 3/2/17.
//

#include "Worklist.h"

Worklist::Worklist(CSR graph, int32_t delta) : csr(graph), delta(delta), relaxCount(0) {
    buckets = map<long, set<int32_t>>();
    vector<vector<int32_t>> vals = graph.iterate();
    int32_t w = 0;

    for(auto it = vals.begin(); it != vals.end(); ++it){
        w = it->at(0);
        long i = floor(graph.getTent(w)/delta);
        if(buckets.find(i) == buckets.end()) buckets[i] = set<int32_t>();
        buckets[i].insert(w);
    }

    cout << "buckets: ";
    cout << "{";
    for(auto i = buckets.begin(); i != buckets.end(); ++i){
        cout << i->first << ": " ;
        cout << "(";
        for(auto it = i->second.begin(); it != i->second.end(); ++it){
            cout << *it << " ";
        }
        cout << ") ";
    }
    cout << "}" << endl;

    light = set<vector<int32_t>>();
    heavy = set<vector<int32_t>>();
}

bool Worklist::hasElements() {
    for(auto it = buckets.begin(); it != buckets.end(); ++it){
        if(it->second.size() != 0) return true;
    }
    return false;
}

long Worklist::getIndex() {
    for(auto it = buckets.begin(); it != buckets.end(); ++it)
        if(it->second.size() > 0) {
            cout << "key: " << it->first << endl;
            return it->first;
        }

    return -1;
}

set<int32_t> Worklist::get(long i) {
    return buckets[i];
}

void Worklist::put(long i, set<int32_t> nodes) {
    buckets[i] = nodes;
}

void Worklist::relax(int32_t w, long d) {
    ++relaxCount;
    long tentCost = csr.getTent(w);
    if(d < tentCost){
        csr.setTent(w, d);
        long i = floor(tentCost/delta);
        if(buckets[i].find(w) != buckets[i].end()) buckets[i].erase(w);
        long newInd = floor(d/delta);
        if(buckets.find(newInd) == buckets.end())
            buckets[newInd] = set<int32_t>({w});
        else buckets[newInd].insert(w);
    }
}

void Worklist::relaxNodes(set<csrTuple> req) {
//    cout << "Worklist::relaxNodes()" <<endl;
    vector<csrTuple> reqVector(req.begin(), req.end());
    random_shuffle(reqVector.begin(), reqVector.end());

    for (auto it = reqVector.begin(); it != reqVector.end(); ++it) {
        relax(it->first, it->second);
    }
}

void Worklist::printRelaxCount() {
    cout << "Relaxations: " << relaxCount << endl;
}

set<vector<int32_t>> Worklist::getLight() {
    return light;
}

set<vector<int32_t>> Worklist::getHeavy() {
    return heavy;
}

void Worklist::setLight(set<vector<int32_t>> s) {
    light = s;
}

void Worklist::setHeavy(set<vector<int32_t>> s) {
    heavy = s;
}

