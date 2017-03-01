#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include "CSR.h"

class CSR {
    private:
        std::vector<int32_t> value;
        std::vector<int32_t> IA;
        std::vector<int32_t> JA;
        int32_t num_rows;
        int32_t num_cols;

    public:
        CSR(int32_t num_rows);
        int32_t get(int32_t x, int32_t y);
        void put(int32_t x, int32_t y, int32_t v);
};

int32_t CSR::get(int32_t x, int32_t y) {
    int32_t prev_row_values_count = IA.at(x);
    int32_t current_row_valid_count = IA.at(x + 1);

    int32_t i;
    int32_t result;
    for (i = prev_row_values_count; i < current_row_valid_count; ++i) {
        if (IA.at(i) == y) {
            result = value.at(i);
            break;
        }
        else {
            result = 0;
            break;
        }
    }
    return result;
}

void CSR::put(int32_t x, int32_t y, int32_t v) {
    int32_t i;
    for (i = x + 1; i < num_rows + 1; ++i) {
        IA.at(i) += 1;
    }

    int32_t previous_row_values_count = IA.at(x);
    bool inserted;

    int32_t j; 
    for (j = previous_row_values_count; j < IA.at(x + 1) - 1; ++i) {
        if (JA.at(j) > y) {
            JA.at(j) = y;
            value.at(y) = v;
            inserted = 1;
            break;
        }
        else if (JA.at(j) == y) {
            inserted = 1;
            value.at(j) = v;
        }
    }

    if (!inserted) {
        int32_t idx = IA.at(x + 1) - 1;
        JA.at(idx) = y;
        value.at(idx) = y;
    }
}

CSR::CSR(int32_t num_rows) {
    std::fill(IA.begin(), IA.end(), 0);
    num_rows = num_rows;
    num_cols = num_rows;
}

