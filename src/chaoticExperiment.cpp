#include <string>
#include <cstring>
#include "SSSP.h"
#include "Parser.h"

int main(){
    Parser p = Parser();
    CSR csr = p.parseInput();

    cout << "Random seed: 10" << endl;
    clock_t t;
    DeltaStep deltaStep = DeltaStep(csr, INT_MAX, 10);
    deltaStep.run(false, true);
    t = clock() - t;
    cout << "Delta step algorithm with chaotic relaxation took " << ((float)t)/CLOCKS_PER_SEC << " seconds" << endl;

    cout << "Random seed: 20" << endl;
    clock_t x;
    deltaStep = DeltaStep(csr, INT_MAX, 20);
    deltaStep.run(false, true);
    x = clock() - x;
    cout << "Delta step algorithm with chaotic relaxation took " << ((float)x)/CLOCKS_PER_SEC << " seconds" << endl;

    cout << "Random seed: 50" << endl;
    clock_t y;
    deltaStep = DeltaStep(csr, INT_MAX, 50);
    deltaStep.run(false, true);
    y = clock() - y;
    cout << "Delta step algorithm with chaotic relaxation took " << ((float)y)/CLOCKS_PER_SEC << " seconds" << endl;


    return 0;
}
