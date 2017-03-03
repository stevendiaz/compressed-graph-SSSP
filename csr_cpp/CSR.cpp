#include "CSR.h"

/* CSRImpl Class Methods */
CSR::CSR(int32_t size) : size(size) {
    value = vector<int32_t>();
    IA = vector<int32_t>(size + 1, 0);
    JA = vector<int32_t>(size, 0);
    seenNodes = map < csrTuple, int32_t > ();
    nodeLabels = vector<int32_t>(size, 0);
}

void CSR::updateValue(int32_t x, int32_t y, int32_t val) {
//    cout << "CSR::updateValue" << endl;
    int32_t preVRowVal = IA[x];
    bool inserted = false;
    auto it = value.begin();

//    cout << "for loop:" << endl;
//    cout << "preVRowVal = " << preVRowVal << endl;
//    cout << "IA[x + 1] - 1 = " << IA[x + 1] - 1 << endl;
    for (int j = preVRowVal; j < IA[x + 1] - 1; ++j) {
//        cout << "j = " << j << endl;
        /* COME BACK FOR CLEANING UP!!! */
        if (JA[j] > y) {
            JA[j] = val;
            value.insert(it + j, val);
            inserted = true;
            break;
        } else if (JA[j] == y) {
            inserted = true;
            value.insert(it + j, val);
            break;
        }
    }

    //Fall safe
    if (!inserted) {
        JA[IA[x + 1] - 1] = y;
        value.insert(it + IA[x + 1] - 1, val);
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
    //cout << "CSR::set" << endl;
    csrTuple coordinate(x, y);
    if (seenNodes.find(coordinate) == seenNodes.end()) {
        cout << x << " " << y << endl;
        for (int i = x + 1; i < size; ++i)
            ++IA[i];
        updateValue(x, y, val);
    } else if (val > get(x, y)) updateValue(x, y, val);
}

vector <vector<int32_t>> CSR::iterate() {
    //cout << "CSR::iterate" << endl;
    vector <vector<int32_t>> result;

    for (size_t i = 0; i < IA.size(); ++i) {
        if (i != 0) {
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
    }
    return result;
}

void CSR::printNodeLabels() {
    for (size_t i = 0; i < nodeLabels.size(); ++i)
        cout << i << " " << nodeLabels[i];
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

int32_t CSR::getTent(int32_t u) {
    return nodeLabels[u];
}

void CSR::setTent(int32_t u, int32_t val) {
    nodeLabels[u] = val;
}


///* << overloading */
//ostream &operator<<(ostream &os, CSR const &data) {
//    vector <vector<int32_t>> vals = data.iterate();
//    size_t n = vals.size();
//    os << "p sp " << data.size << " " << data.value.size() << endl;
//    for (uint32_t i = 0; i < n; ++i) {
//        os << "a " << vals.at(i).at(0) << " " << vals.at(i).at(1) << " " << vals.at(i).at(2) << endl;
//    }
//
//    return os;
//}