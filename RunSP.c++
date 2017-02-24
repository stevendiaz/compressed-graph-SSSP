#include <iostream> // endl, istream, ostream
#include "CSR.h"

using namespace std;

void test() {
    string::size_type size = 4;
    CSR graph = CSR(size);
    graph.put(1, 0, 5);
    //graph.put(1, 1, 8);
    //graph.put(2, 2, 3);
    //graph.put(3, 1, 6);
    //cout << "A[1][0] = " << graph.get(1, 0) << endl;

}

int main() {
    test();
    return 0;
}
