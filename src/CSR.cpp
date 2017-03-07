#include "CSR.h"

/* CSRImpl Class Methods */
CSR::CSR(int32_t size) : size(size + 1), currSrc(1), NNZ(0), outDegreeNode(0), largestOutDegree(0), currOutDegree(0) {
    size += 1;
    value = vector<int32_t>();
    IA = vector<int32_t>(size, 0);
    JA = vector<int32_t>();
    currSrc = 1;
    seenNodes = vector<int32_t > (size, -1);
    nodeLabels = vector<long>(size, INT_MAX);
    relaxMap = map<int32_t, set<int32_t>>();
    tempJA = vector<int32_t>();
}

void CSR::update(int32_t x){
    //Update CSR arrays
    IA.at(x - 1) = NNZ + IA.at(x - 2);
    cout << "NNZ =  "<< NNZ << endl;

    NNZ = 0;
    sort(tempJA.begin(), tempJA.end());
    JA.insert(JA.end(), tempJA.begin(), tempJA.end());

    for(auto it = tempJA.begin(); it != tempJA.end(); ++it)
        value.push_back(seenNodes[*it]);

    //Update largest out-degree and node with largest out-degree
    if(currOutDegree > largestOutDegree){
        largestOutDegree = currOutDegree;
        currOutDegree = 0;
        outDegreeNode = currSrc;
    }

    //update current source node
    currSrc = x;
    debugInfo();
}

void CSR::put(int32_t x, int32_t y, int32_t val) {
    if(relaxMap.find(x) == relaxMap.end()) relaxMap[x] = set<int32_t>({y});
    else relaxMap[x].insert(y);
    
    if(currSrc < x){
        update(x);
        seenNodes = vector<int32_t>(size, -1);
        tempJA = vector<int32_t>();
    }

    cout << "x = " << x << ", y = " << y << endl;
    
    if(seenNodes[y] == -1){
        ++NNZ;
        tempJA.push_back(y);
        seenNodes[y] = val;
        ++currOutDegree;
    } else {
        if(seenNodes[y] < val) value.at(y) = val;
    }
}

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

bool CSR::nodeFullyRelaxed(int32_t node){
    return relaxMap[node].size() == 0;
}

void CSR::relaxNode(int32_t src, int32_t dest){
    if(relaxMap[src].find(dest) != relaxMap[src].end())
        relaxMap[src].erase(dest);
}
