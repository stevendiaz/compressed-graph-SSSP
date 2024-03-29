//
// Created by Jia Li on 3/2/17.
//

#include "SSSP.h"
#include "Worklist.h"


DeltaStep::DeltaStep(CSR csr, int32_t step, int seed) : csr(csr), delta(step), seed(seed) {}

/* @param bool printLabels: flag for printing node labels
 * @param bool printRelaxCount: flag for printing relaxations
 * public method: 
 *      runs the delta-step algorithm
 */
void DeltaStep::run(bool printLabels, bool printRelaxCount) {
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
    }

    Worklist worklist = Worklist(csr, delta, seed);
    worklist.setLight(tempLight);
    worklist.setHeavy(tempHeavy);
    worklist.relax(1, 0);
    while(worklist.hasElements()){
        set<int32_t> s;
        long i = worklist.getIndex();
        while(!worklist.get(i).empty()){
            set<int32_t> bucket = worklist.get(i);
            set<csrTuple> req = worklist.match(bucket, worklist.getLight());
            s.insert(bucket.begin(), bucket.end());
            worklist.put(i, set<int32_t>());
            worklist.relaxNodes(req, seed);
        }
        set<csrTuple> req = worklist.match(s, worklist.getHeavy());
        worklist.relaxNodes(req, seed);
    }
    if(printLabels) worklist.csr.printNodeLabels();
    if(printRelaxCount )worklist.printRelaxCount();
}
