#include <ctime>
#include <cmath>
#include <iostream>
#include "SSSP.h"
#include "Parser.h"



int main(){
    Parser p = Parser(316607);
    CSR csr = p.parseInput();

    clock_t t;
    DeltaStep deltaStep(csr, 1, 10);
    deltaStep.run(false, true);
    t = clock() - t;
    cout << "Optimal delta step algorithm took " << ((float)t)/CLOCKS_PER_SEC<< "seconds" << endl;

    return 0;
}