#include <string>
#include <ctime>
#include <cstring>
#include "SSSP.h"
#include "Parser.h"

int main(){
    Parser p = Parser ();

    clock_t t = clock();
	CSR csr = p.parseInput();

    t = clock() - t;
//    cout << "CSR: " << ((float)t)/CLOCKS_PER_SEC<< "seconds" << endl;
    DeltaStep deltaStep = DeltaStep(csr, 1, 10);
    deltaStep.run(true, true);
//    t = clock() - t;
//    cout << "delta: " << ((float)t)/CLOCKS_PER_SEC<< "seconds" << endl;

    return 0;
}