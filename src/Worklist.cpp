//
// Created by Jia Li on 3/2/17.
//

#include "SSSP.h"
#include "Worklist.h"

Worklist::Worklist(CSR graph, int32_t delta) : csr(graph), delta(delta), relaxEdgeCount(0), relaxNodeCount(0) {
    buckets = map<long, set<int32_t>>();
    vector<vector<int32_t>> vals = graph.iterate();
    int32_t w = 0;

    for(auto it = vals.begin(); it != vals.end(); ++it){
        w = it->at(0);
        long i = floor(graph.getTent(w)/delta);
        if(buckets.find(i) == buckets.end()) buckets[i] = set<int32_t>();
        buckets[i].insert(w);
    }

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
    ++relaxEdgeCount;
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


void Worklist::relaxNodes(set<csrTuple> req, int seed) {
    vector<csrTuple> reqVector(req.begin(), req.end());
    random_shuffle(reqVector.begin(), reqVector.end());

    for (auto it = reqVector.begin(); it != reqVector.end(); ++it) {
        relax(it->first, it->second);
    }
}

void Worklist::printRelaxCount() {
    cout << "Edge relaxations: " << relaxEdgeCount << endl;
    cout << "Node relaxations: " << relaxNodeCount << endl;
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

set<csrTuple> Worklist::match(set<int32_t> bucket, set<vector<int32_t>> s) {
    set<csrTuple> result;

    for(auto edge = s.begin(); edge != s.end(); ++edge) {
        if(bucket.find(edge->at(0)) != bucket.end()) {
            csr.relaxNode(edge->at(0), edge->at(1));
            if(csr.nodeFullyRelaxed(edge->at(0))) ++relaxNodeCount;
	    
            csrTuple t(edge->at(1), csr.getTent(edge->at(0)) + edge->at(2));
            result.insert(t);
        }
    }
    return result;
}
