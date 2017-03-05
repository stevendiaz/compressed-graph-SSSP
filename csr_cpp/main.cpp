//
// Created by Jia Li on 3/2/17.
//

#include "util.h"



int main(){
    CSR csr = parseInput();
    DeltaStep deltaStep = DeltaStep(csr, 1);
    deltaStep.run();

    return 0;
}