#include <iostream> // endl, istream, ostream
#include "CSR.h"

using namespace std;

void test() {
    string::size_type size = 4;
    CSR graph = CSR(size);
    graph.put(1, 0, 5);
    graph.put(1, 1, 8);
    graph.put(2, 2, 3);
    graph.put(3, 1, 6);
    cout << "A[1][0] = " << graph.get(1, 0) << endl;
    cout << "A[1][1] = " << graph.get(1, 1) << endl;
    cout << "A[2][2] = " << graph.get(2, 2) << endl;
    cout << "A[3][1] = " << graph.get(3, 1) << endl;
    vector< vector<int32_t> > result = graph.iterate();
    size_t n = result.size();
    size_t m = result.at(0).size();
    cout << "[";
    for(size_t i = 0; i < n; ++i) {
        cout << "(";
        for(size_t j = 0; j < m; ++j) {
            cout << result.at(i).at(j) << " ";
        }
        cout << "),";
    }
    cout << "]" << endl; 

}

int main() {
    test();
    return 0;
}
