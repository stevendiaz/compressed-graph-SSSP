//
// Created by Jia Li on 3/5/17.
//

#include "Parser.h"
#include "CSR.h"

int main(){
    Parser p = Parser();
    CSR csr = p.parseInput();
    cout << "The largest out-degree is " << csr.getLargestOutDegree() << endl;

    return 0;
}