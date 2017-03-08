#include "CSR.h"

/* CSRImpl Class Methods */
CSR::CSR(int32_t size, int32_t numEdges) : size(size + 1), numEdges(numEdges), currSrc(1), NNZ(0), outDegreeNode(0), largestOutDegree(0), currOutDegree(0) {
    size += 1;
    value = vector<int32_t>();
    IA = vector<int32_t>({0, 0});
    JA = vector<int32_t>();
    currSrc = 1;
    seenNodes = vector<int32_t > (size, -1);
    nodeLabels = vector<long>(size, INT_MAX);
    relaxMap = map<int32_t, set<int32_t>>();
    tempJA = vector<int32_t>();
}

void CSR::update(int32_t x, int end){
    //Update JA
    sort(tempJA.begin(), tempJA.end());
    JA.insert(JA.end(), tempJA.begin(), tempJA.end());

    //Update Value
    for (auto it = tempJA.begin(); it != tempJA.end(); ++it)
        value.push_back(seenNodes[*it]);

    //Update IA
    while(x <= end) {
        //Update CSR arrays
        IA.push_back(NNZ);

        //update current source node
        ++currSrc;
        ++x;
    }

    //Update largest out-degree and node with largest out-degree
    if (currOutDegree > largestOutDegree) {
        largestOutDegree = currOutDegree;
        currOutDegree = 0;
        outDegreeNode = currSrc;
    }
}

void CSR::put(int32_t x, int32_t y, int32_t val) {
    if(relaxMap.find(x) == relaxMap.end()) relaxMap[x] = set<int32_t>({y});
    else relaxMap[x].insert(y);

    //Skip all 0-outDegree nodes from current source and update current source node
    if(currSrc < x) {
        update(currSrc + 1, x);
        seenNodes = vector<int32_t>(size, -1);
        tempJA = vector<int32_t>();
    }

    if(seenNodes[y] == -1){
        ++NNZ;
        tempJA.push_back(y);
        seenNodes[y] = val;
        ++currOutDegree;
    } else {
        if(seenNodes[y] < val) seenNodes[y] = val;
    }
}

vector <vector<int32_t>> CSR::iterate() {
    vector <vector<int32_t>> result;

    for (size_t i = 1; i < IA.size(); ++i) {
        int32_t currentRowIndex = 0;

        while (currentRowIndex < IA[i] - IA[i - 1]) {
            int32_t rowVal = i - 1;
            int32_t colVal = JA[IA[i - 1] + currentRowIndex];
            int32_t realVal = value[IA[i - 1] + currentRowIndex];

            vector <int32_t> pairing{rowVal, colVal, realVal};
            result.push_back(pairing);
            ++currentRowIndex;
        }
    }
    return result;
}

void CSR::printNodeLabels() {
    cout << "0 INF" << endl;
    for (size_t i = 1; i < nodeLabels.size(); ++i){
        cout << i << " ";
        if (nodeLabels[i] == INT_MAX) cout << "INF" << endl;
        else cout << nodeLabels[i] << endl;
    }

}

int32_t CSR::getOutDegreeNode() {
    return outDegreeNode;
}

long CSR::getTent(int32_t u) {
    return nodeLabels[u];
}

void CSR::setTent(int32_t u, long val) {
    nodeLabels[u] = val;
}

void CSR::debugInfo() {
    cout << "value: " << value.size() << endl;
    for(auto it = value.begin(); it != value.end(); ++it)
        cout << *it << " ";
    cout << endl;

    cout << "IA: " << IA.size() << endl;
    for(auto it = IA.begin(); it != IA.end(); ++it)
        cout << *it << " ";
    cout << endl;

    cout << "JA: " << JA.size() << endl;
    for(auto it = JA.begin(); it != JA.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

bool CSR::nodeFullyRelaxed(int32_t node){
    return relaxMap[node].size() == 0;
}

void CSR::relaxNode(int32_t src, int32_t dest){
    if(relaxMap[src].find(dest) != relaxMap[src].end())
        relaxMap[src].erase(dest);
}

void CSR::to_dimacs() {
    cout << "p sp " << size - 1 << " " <<  numEdges << endl;

    vector<vector<int32_t> > edges = iterate();
    for(auto it = edges.begin(); it != edges.end(); ++it) {
        int32_t u = it->at(0);
        int32_t v = it->at(1);
        int32_t w = it->at(2);
        cout << "a " << u << " " << v << " " << w << endl;
    }
}
