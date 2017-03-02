#include "CSR.h"


/* << overloading */
ostream &operator<<(ostream &os, CSR const &data) {
    vector<vector<int32_t>> vals = iterate();
    size_t n = vals.size();
    os << "p sp " << data.numRows << " " << data.value.size() << endl;
    for(uint32_t i = 0; i < n; ++i) {
        os << "a " << vals.at(i).at(0) << " " << vals.at(i).at(1) << " " << vals.at(i).at(2) << endl;
    }

    return os;
}

/* CSRImpl Class Methods */
CSR::CSR(int32_t rows, int32_t cols) : numRows(rows), numCols(cols) {
    value = vector<int32_t>();
    IA = vector<int32_t>(rows + 1, 0);
    JA = vector<int32_t>(cols, 0);
    seenNodes = unordered_map<pair<int32_t, int32_t>, int32_t>();
    nodeLabels = vector<int32_t>(rows, 0);
}

void CSR::updateValue(int32_t x, int32_t y, int32_t val){
    int32_t preVRowVal = IA[x];
    bool inserted = 0;
    for(int j = preVRowVal; j < IA[x+1] - 1; ++j){
        /* COME BACK FOR CLEANING UP!!! */
        if(JA[j] > y){
            JA[j] = val;
            value[j] = val;
            inserted = 1;
            break;
        } else if(JA[j] == y){
            inserted = 1;
            value[j] = val;
            break;
        }
    }

    //Fall safe
    if(!inserted){
        JA[IA[x+1] - 1] = y;
        value[IA[x+1] - 1] = val;
    }

    //Mark (x, y) visited
    pair <int32_t, int32_t> coordinate (x, y);
    seenNodes[coordinate] = val;
}

int32_t CSR::get(int32_t x, int32_t y){
    int32_t entry = IA[x+1] - IA[x];
    for (int i = IA[x]; i < IA[x+1]; ++i){
        if(JA[i] == y) return value[i];
    }
    return 0;
}

void CSR::set(int32_t x, int32_t y, int32_t val){
    pair <int32_t, int32_t> coordinate (x, y);
    auto it = seenNodes.find(coordinate);
    if(it == seenNodes.end()){
        cout << x << " " << y << endl;
        for(int i = x+1; i < numRows; ++i)
        ++IA[i];
        updateValue(x, y, val);
    }
    else
        if(val > get(x, y)) updateValue(x, y, val);
}

vector<vector<int32_t>> CSR::iterate(){
    vector<vector<int32_t>> result;
    auto iaIt = IA.begin();

    for(int32_t i = 0; i < IA.size(); ++i){
        if(i != 0){
            int32_t currentRowIndex = 0;
            while (currentRowIndex < IA.at(i) - IA.at(i - 1)){
                int32_t rowVal = i - 1;
                int32_t colVal = JA.at(IA.at(i - 1) + currentRowIndex);
                int32_t realVal = value.at(IA.at(i - 1) + currentRowIndex);

                vector<int32_t> pairing{rowVal, colVal, realVal};
                result.push_back(pairing);
                ++currentRowIndex;
            }
        }
    }
    return result;
}

void CSR::printNodeLabels(){
    for(int i = 0; i < nodeLabels.size(); ++i)
        cout << i << " " << nodeLabels[i];
}

int32_t CSR::getLargestOutDegree(){
    int32_t oldDegree = -1;
    int32_t row = -1;

    for(int i = 0; i < numRows){
        int32_t currDegree = IA[i + 1] - IA[i];
        if(currDegree > oldDegree){
            row = i;
            oldDegree = currDegree;
        }
    }

    return row;
}
