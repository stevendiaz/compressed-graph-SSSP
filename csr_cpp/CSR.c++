#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "CSR.h"

//CSRImpl Class Methods
CSR::CSR(int32_t size) : numRows(size), numCols(size) {
    IA = vector<int>(rows + 1, 0);
    //value =
    //JA =
}

int32_t CSR::get(int x, int y){
    int32_t prevRowValuesCount = IA.at(x);
    int32_t current_row_valid_count = IA.at(x + 1);
    for(int32_t i = prevRowValuesCount; i < currentRowValidCount; ++i) {
        if (JA.at(i) == y) {
            return value.at(i);
        }
    }
    return -1;
}

// CSR::set(int x, int y){}

vector<int32_t[]> CSR::iterate(){
    vector<int32_t[]> result;
    for(int32_t i = 0; i < IA.size(); ++i){
        if(i != 0){
            int32_t currentRowIndex = 0;
            while (currentRowIndex < IA.at(i) - IA.at(i - 1)){
                int32_t rowVal = i - 1;
                int32_t colV = JA.at(IA.at(i - 1) + currentRowIndex);
                int32_t realVal = value.at(IA.at(i - 1) + currentRowIndex);

                int32_t pairing[3];
                pairing[0] = rowVal;
                pairing[1] = colVal;
                pairing[2] = realVal;
                result.push_back(pairing);
                ++currentRowIndex;
            }
        }
    }
    return result;
}

void CSR::put(int32_t x, int32_t y, int32_t v){
    for (int32_t i = x + 1; i < num_rows + 1; ++i) {
        cout << "IA size line27: " << IA.size() << endl;
        cout << "index of IA: " << i << endl;
        ++(IA.at(i));
    }

    int32_t previousRowValuesCount = IA.at(x);

    bool inserted = 0;
    // cout << "i: " << previous_row_values_count << " j: " << IA.at(x + 1) - 1 << std::endl;
    for (int32_t j = previous_row_values_count; j < IA.at(x + 1) - 1; ++j) {
        cout << "Loop Enter" << endl;
        cout << "Index: " << j << " JA size: " << JA.size() << " Val size: " << value.size() << endl;
        if (JA.at(j) > y) {
            vector<int32_t>::iterator JA_it = JA.begin();
            vector<int32_t>::iterator value_it = value.begin();
            JA.insert(JA_it + j, y);
            value.insert(value_it + j, v);
            inserted = 1;
            break;
        }
        else if (JA.at(j) == y) {
            inserted = 1;
            vector<int32_t>::iterator value_it = value.begin();
            value.insert(value_it+j, v);
            break;
        }
    }

    if (!inserted) {
        int32_t idx = IA.at(x + 1) - 1;
        cout << "Line 62: index: " << idx << " JA size: " << JA.size() << " val size: " << value.size() << endl;
        if (JA.size() == 0 && value.size() == 0) {
            JA.push_back(y);
            value.push_back(v);
        }
        else if((int)JA.size() == idx && (int)value.size() == idx) {
            JA.push_back(y);
            value.push_back(v);
        }
        else {
            vector<int32_t>::iterator JA_it = JA.begin();
            vector<int32_t>::iterator value_it = value.begin();
            JA.insert(JA_it + idx, y);
            value.insert(value_it + idx, v);
        }
    }
}
