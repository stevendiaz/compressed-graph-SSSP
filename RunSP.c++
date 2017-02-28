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
    graph.print_dimacs(); 
}

int main() {
    test();
    return 0;
}
