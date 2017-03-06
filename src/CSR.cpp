#include "CSR.h"

/* CSRImpl Class Methods */
CSR::CSR(int32_t size) : size(size + 1) {
    size += 1;
    value = vector<int32_t>();
    IA = vector<int32_t>(size + 1, 0);
    JA = vector<int32_t>();
    nodeLabels = vector<long>(size, INT_MAX);
    relaxMap = map<int32_t, set<int32_t>>();
}

void CSR::updateValue(int32_t x, int32_t y, int32_t val) {
//    cout << "update" << endl;
    int32_t prevRowVal = IA[x];
    int32_t currRowVal = IA[x + 1] - 1;
    bool inserted = false;
    auto jit = JA.begin();
    auto vit = value.begin();

    for (int j = prevRowVal; j < currRowVal; ++j) {
//        cout << "oui" << endl;
        if (JA.at(j) > y) {
//            cout <<"if" << endl;
            JA.insert(jit + j, y);
            value.insert(vit + j, val);
            inserted = true;
            break;
        } else if (JA.at(j) == y) {
//            cout << "else if" << endl;
            inserted = true;
            value.at(j) = val;
            break;
        }
    }

    //Fall safe
    if (!inserted) {
//        cout << "fall safe" << endl;
//        cout << IA[x + 1] - 1 << ", " << JA.size() <<endl;
        if(JA.size() <= currRowVal){
            //Seg fault without this condition
            //JA.size() at this point could be smaller than currRowval
            //Prob because returning -1 in get when range invalid
            JA.resize(currRowVal);
            value.resize(currRowVal);
        }
        JA.insert(jit + currRowVal, y);
        value.insert(vit + currRowVal, val);
    }
//    cout << "leaving update" << endl;
}

int32_t CSR::get(int32_t x, int32_t y) {
    //Return -1 if invalid range -> shouldn't worry right now (this is probably not correct)
    if(x >= IA.size()) return -1;
    for (int i = IA[x]; i < IA[x + 1]; ++i) {
        //Invalid
        if(i >= JA.size()) return -1;
        if (JA[i] == y) return value[i];
    }
    //Never seen and valid range
    return 0;
}

void CSR::put(int32_t x, int32_t y, int32_t val) {
    if(relaxMap.find(x) == relaxMap.end()) relaxMap[x] = set<int32_t>({y});
    else relaxMap[x].insert(y);

    if(get(x, y) == 0){
        for (int i = x + 1; i <= size; ++i){
            ++IA[i];
        }
        updateValue(x, y, val);
    } else if (val > get(x, y) && get(x, y) != -1) updateValue(x, y, val);
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

bool CSR::nodeFullyRelaxed(int32_t node){
    return relaxMap[node].size() == 0;
}

void CSR::relaxNode(int32_t src, int32_t dest){
    if(relaxMap[src].find(dest) != relaxMap[src].end())
        relaxMap[src].erase(dest);
}
