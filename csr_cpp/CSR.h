#include <stdint.h>
// #include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

class CSR {
private:
    vector<int32_t> value;
    vector<int32_t> IA;
    vector<int32_t> JA;
    int32_t numRows;
    int32_t numCols;

public:
    CSR (int32_t size);

    vector<vector<int32_t>> iterate();
    void put(int32_t x, int32_t y, int32_t v);
    int32_t get(int32_t x, int32_t y);

    void print_dimacs() {
        vector< vector<int32_t> > vals = iterate();
        size_t n = vals.size();
        cout << "p sp " << num_rows << " " << value.size() << endl;
        for(uint32_t i = 0; i < n; ++i) {
            cout << "a " << vals.at(i).at(0) << " " << vals.at(i).at(1) << " " << vals.at(i).at(2) << endl;
        }
    }
};
