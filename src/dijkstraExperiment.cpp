#include <string>
#include <cstring>
#include "SSSP.h"
#include "Parser.h"

int main(){
    Parser p = Parser (1);
    CSR csr = p.parseInput();
    DeltaStep deltaStep = DeltaStep(csr, 1, 10);
    deltaStep.run(true, true);

    return 0;
}