#include "CSR.h"

/* CSRImpl Class Methods */

/* @param int32_t size: Number of nodes, represents a size*size matrix
 * @return CSR : an empty compressed sparse row object
 */
CSR::CSR(int32_t size) : size(size + 1) {
    size += 1;
    value = vector<int32_t>();
    IA = vector<int32_t>(size + 1, 0);
    JA = vector<int32_t>();
    seenNodes = map < csrTuple, int32_t > ();
    nodeLabels = vector<long>(size, INT_MAX);
    relaxMap = map<int32_t, set<int32_t>>();
}

/* @param int32_t x: x value in the adjaceny matrix, the from node label
 * @param int32_t y: y value in the adjaceny matrix, the to node label
 * @param int32_t val: the weight in the adjaceny matrix
 * private method: 
 *      If the value has been set before, make proper adjustments to 
 *      internal datastructures. 
 */
void CSR::updateValue(int32_t x, int32_t y, int32_t val) {
    int32_t preVRowVal = IA[x];
    bool inserted = false;
    auto jit = JA.begin();
    auto vit = value.begin();

    for (int j = preVRowVal; j < IA[x + 1] - 1; ++j) {
        if (JA.at(j) > y) {
            JA.insert(jit + j, y);
            value.insert(vit + j, val);
            inserted = true;
            break;
        } else if (JA.at(j) == y) {
            inserted = true;
            value.at(j) = val;
            break;
        }
    }

    //Fall safe
    if (!inserted) {
        JA.insert(jit + IA[x + 1] - 1, y);
        value.insert(vit + IA[x + 1] - 1, val);
    }

    //Mark (x, y) visited
    csrTuple coordinate(x, y);
    seenNodes[coordinate] = val;
}

/* @param int32_t x: x value in the adjaceny matrix, the from node label
 * @param int32_t y: y value in the adjaceny matrix, the to node label
 * public method: 
 *      fetches the data at x,y in the adjaceny matrix
 * @return int32_t: the weight of the edge from x to y
 */
int32_t CSR::get(int32_t x, int32_t y) {
    for (int i = IA[x]; i < IA[x + 1]; ++i) {
        if (JA[i] == y) return value[i];
    }
    return 0;
}

/* @param int32_t x: x value in the adjaceny matrix, the from node label
 * @param int32_t y: y value in the adjaceny matrix, the to node label
 * @param int32_t val: the weight in the adjaceny matrix
 * public method: 
 *      sets the weight of edge x to y to val
 */
void CSR::put(int32_t x, int32_t y, int32_t val) {
    csrTuple coordinate(x, y);
    if(relaxMap.find(x) == relaxMap.end()) relaxMap[x] = set<int32_t>({y});
    else relaxMap[x].insert(y);

    if (seenNodes.find(coordinate) == seenNodes.end()) {
        for (int i = x + 1; i <= size; ++i){
            ++IA[i];
        }
        updateValue(x, y, val);
    } else if (val > get(x, y)) updateValue(x, y, val);
}

/* 
 * public method: 
 *      returns a set of all the edges in the graph
 *      each vector will be of the from <to, from, weight>
 */
vector <vector<int32_t>> CSR::iterate() {
    vector <vector<int32_t>> result;

    for (size_t i = 1; i < IA.size(); ++i) {
        int32_t currentRowIndex = 0;

        while (currentRowIndex < IA.at(i) - IA.at(i - 1)) {
            int32_t rowVal = i - 1;
            int32_t colVal = JA.at(IA.at(i - 1) + currentRowIndex);
            int32_t realVal = value.at(IA.at(i - 1) + currentRowIndex);

            vector <int32_t> pairing{rowVal, colVal, realVal};
            result.push_back(pairing);
            ++currentRowIndex;
        }
    }
    return result;
}

/* 
 * public method: 
 *      Prints the tentative cost of all the nodes
 */
void CSR::printNodeLabels() {
    cout << "0 INF" << endl;
    for (size_t i = 1; i < nodeLabels.size(); ++i){
        cout << i << " ";
        //if(IA[i+1] - IA[i-1] == 0) cout << 0 << endl;
        if (nodeLabels[i] == INT_MAX) cout << "INF" << endl;
        else cout << nodeLabels[i] << endl;
    }

}


/* @param int32_t u: node id
 * public method: 
 *      gets the tentative cost of node u
 * @return long: tentative cost of node u
 */
long CSR::getTent(int32_t u) {
    return nodeLabels[u];
}

/* @param int32_t u: node id
 * @param int32_t v: tentative cost to be set
 * public method: 
 *      sets the weight of edge x to y to val
 */
void CSR::setTent(int32_t u, long val) {
    nodeLabels[u] = val;
}

/* 
 * public method: 
 *      prints all inner datastructures of CSR
 */
void CSR::debugInfo() {
    cout << "value: ";
    for(auto it = value.begin(); it != value.end(); ++it)
        cout << *it << " ";
    cout << endl;

    cout << "IA: ";
    for(auto it = IA.begin(); it != IA.end(); ++it)
        cout << *it << " ";
    cout << endl;

    cout << "JA: ";
    for(auto it = JA.begin(); it != JA.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

/* 
 * public method: 
 *      gets the node with the largest outdegree
 * @return int32_t: node with the largest out degree
 */
int32_t CSR::getLargestOutDegree() {
   int32_t oldDegree = -1;
   int32_t row = -1;

   for (int i = 0; i < size; ++i) {
       int32_t currDegree = IA[i + 1] - IA[i];
       if (currDegree > oldDegree) {
           row = i;
           oldDegree = currDegree;
       }
   }
   return row;
}

/* @param int32_t node: node id
 * public method: 
 *      checks if node has had all it's edges relaxed
 * @return bool: true if all edges have been relax, false otherwise
 */
bool CSR::nodeFullyRelaxed(int32_t node){
    return relaxMap[node].size() == 0;
}

/* @param int32_t src: to edge
 * @param int32_t dest: from edge
 * public method: 
 *      sets edge src->dest as relaxed
 */
void CSR::relaxNode(int32_t src, int32_t dest){
    if(relaxMap[src].find(dest) != relaxMap[src].end())
        relaxMap[src].erase(dest);
}
