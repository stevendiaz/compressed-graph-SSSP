//
// Created by Jia Li on 3/2/17.
//

#include "Worklist.h"

Worklist::Worklist(int32_t delta, CSR graph) : delta(delta) {
    buckets = map<int32_t, unordered_set<int32_t>>();
    vector<vector<int32_t>> vals = graph.iterate();
    int32_t w = 0;

    for(auto it = vals.begin(); it != vals.end(); ++it){
         w = (*it)[0];
        int32_t i = floor(graph.getTent(w/delta));

        if(buckets.find(i) == buckets.end()) buckets[i] = unordered_set<int32_t>();
        buckets[i].insert(w);
    }
}
//
//bool Worklist::hasElements() {
//    for(auto it = buckets.begin(); it != buckets.end(); ++it){
//        if(it->second.size() != 0) return true;
//    }
//    return false;
//}
//
//int32_t Worklist::getIndex() {
//    for(auto it = buckets.begin(); it != buckets.end(); ++it)
//        if(it->second.size() > 0) return it->first;
//
//    return -1;
//}
//
//unordered_set<int32_t> Worklist::get(int32_t i) {
//    return buckets[i];
//}
//
//void Worklist::set(int32_t i, unordered_set<int32_t> nodes) {
//    buckets[i] = nodes;
//}
//
//void Worklist::relaxNodes(CSR graph, unordered_set<int32_t> req) {
//    vector<int32_t> reqVector(req.begin(), req.end());
//    random_shuffle(reqVector.begin(), reqVector.end());
//
//    for(auto it = reqVector.begin(); it != reqVector.end(); ++it){
//        relax()
//    }
//}
