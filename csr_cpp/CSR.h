#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

#ifndef CSR_h
#define CSR_h

typedef std::pair<int32_t, int32_t> tuple;

using namespace std;

class CSR {
private:
    int32_t size;
    vector<int32_t> value;
    vector<int32_t> IA;
    vector<int32_t> JA;
    map<tuple, int32_t> seenNodes;
    vector<int32_t> nodeLabels;


    void updateValue(int32_t x, int32_t y, int32_t val);

public:
    CSR (int32_t size);

    int32_t get(int32_t x, int32_t y);
    void set(int32_t x, int32_t y, int32_t val);
    vector<vector<int32_t>> iterate();
    void printNodeLabels();
    int32_t getLargestOutDegree();
    int32_t getTent(int32_t u);
    void setTent(int32_t u, int32_t val);

    friend ostream &operator<<(ostream &w, CSR const &data);
};

#endif
