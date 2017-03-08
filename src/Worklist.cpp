//
// Created by Jia Li on 3/2/17.
//

#include "SSSP.h"
#include "Worklist.h"

/* @param CSR graph: inner copy of the CSR
 * @param int32_t delta: value of delta to be run on the algorithm
 * @param int32_t seed: seed used for RNG
 * constructor:
 *	initializes buckets and sets initial light and heavy sets
 */
Worklist::Worklist(CSR graph, int32_t delta, int32_t seed) : csr(graph), delta(delta), relaxEdgeCount(0), relaxNodeCount(0), randomSeed(seed) {
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

/* 
 *  public method:
 *	checks if there are non empty buckets
 *  @return bool: true if there are non empty buckets, false otherwise
 */
bool Worklist::hasElements() {
    for(auto it = buckets.begin(); it != buckets.end(); ++it){
        if(it->second.size() != 0) return true;
    }
    return false;
}

/* 
 *  public method:
 *	returns first non-empty bucket, -1 if there are no nonempty buckets
 *  @return long: index of the first non empty bucket
 */
long Worklist::getIndex() {
    for(auto it = buckets.begin(); it != buckets.end(); ++it)
        if(it->second.size() > 0) {
            return it->first;
        }

    return -1;
}

/*  @param long i: index of the bucket to get
 *  public method:
 *	returns the bucket at index i
 *  @return set<int32_t>: a bucket
 */
set<int32_t> Worklist::get(long i) {
    return buckets[i];
}

/*  @param long i: index of the bucket to set
 *  @param set<int32_t> nodes: the bucket
 *  public method:
 *	sets bucket i to nodes
 */
void Worklist::put(long i, set<int32_t> nodes) {
    buckets[i] = nodes;
}

/*  @param int32_t w: node to be relaxed
 *  @param long d: new tentative cost
 *  public method:
 *	relaxes node w with cost d
 */
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

/*  @param set<csrTuple> req: set of nodes and costs to be relaxed
 *  @param int seed: random seed used for shuffling
 *  public method:
 *	shuffles the nodes and calls relax on each node and cost
 */
int myrandom (int i) { return rand()%i;}

void Worklist::relaxNodes(set<csrTuple> req, int seed) {
    srand (randomSeed);
    vector<csrTuple> reqVector(req.begin(), req.end());
    random_shuffle(reqVector.begin(), reqVector.end(), myrandom);

    for (auto it = reqVector.begin(); it != reqVector.end(); ++it) {
        relax(it->first, it->second);
    }
}

/*  
 *  public method:
 *	prints relaxation counts
 */
void Worklist::printRelaxCount() {
    cout << "Edge relaxations: " << relaxEdgeCount << endl;
    cout << "Node relaxations: " << relaxNodeCount << endl;
}

/* 
 *  public method:
 *	gets light nodes
 *  @return set<vector<int32_t>>: a set of edges
 */
set<vector<int32_t>> Worklist::getLight() {
    return light;
}

/* 
 *  public method:
 *	gets heavy nodes
 *  @return set<vector<int32_t>>: a set of edges
 */
set<vector<int32_t>> Worklist::getHeavy() {
    return heavy;
}

/* @param set<vector<int32_t>> s: a set of edges
 *  public method:
 *	sets light nodes
 */
void Worklist::setLight(set<vector<int32_t>> s) {
    light = s;
}


/* @param set<vector<int32_t>> s: a set of edges
 *  public method:
 *	sets heavy nodes
 */
void Worklist::setHeavy(set<vector<int32_t>> s) {
    heavy = s;
}



/* @param set<vector<int32_t>> s: a set of edges
 * @param set<int32_t>: current bucket (set of nodes)
 *  public method:
 *	finds matches by looking for from nodes in both bucket AND s
 *	makes a result set by returns TO as the node and the tenative cost of the from node with the matched node in s
 * @param set<csrTuple>: cost and weight set
 */
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
