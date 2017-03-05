#include "CSR.h"

/* CSRImpl Class Methods */
CSR::CSR(int32_t size) : size(size + 1) {
    size += 1;
    value = vector<int32_t>();
    IA = vector<int32_t>(size + 1, 0);
    JA = vector<int32_t>();
    seenNodes = map < csrTuple, int32_t > ();
    nodeLabels = vector<long>(size, 0);
}

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

int32_t CSR::get(int32_t x, int32_t y) {
    for (int i = IA[x]; i < IA[x + 1]; ++i) {
        if (JA[i] == y) return value[i];
    }
    return 0;
}

void CSR::put(int32_t x, int32_t y, int32_t val) {
    csrTuple coordinate(x, y);
    if (seenNodes.find(coordinate) == seenNodes.end()) {
//        cout << x << " " << y << endl;
        for (int i = x + 1; i <= size; ++i){
            ++IA[i];
        }
        updateValue(x, y, val);
    } else if (val > get(x, y)) updateValue(x, y, val);
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
        if(IA[i+1] - IA[i-1] == 0) cout << 0 << endl;
        else if (nodeLabels[i] == INT_MAX) cout << "INF" << endl;
        else cout << nodeLabels[i] << endl;
    }

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
