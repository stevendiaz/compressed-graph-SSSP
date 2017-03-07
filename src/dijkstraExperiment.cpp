#include <string>
#include <ctime>
#include <cstring>
#include "SSSP.h"
#include "Parser.h"

int main(){
    Parser p = Parser ();

    clock_t t = clock();
	CSR csr = p.parseInput();
//    csr.debugInfo();
//    DeltaStep deltaStep = DeltaStep(csr, 1, 10);
//    deltaStep.run(true, true);

    return 0;
}