#include <string>
#include <cstring>
#include "SSSP.h"
#include "Parser.h"

int main(){
    Parser p = Parser(140961);
    CSR csr = p.parseInput();

    for(int i = 1; i <= 26; i+=5){
        cout << "step = " << i << endl;
        DeltaStep deltaStep = DeltaStep(csr, i, 10);
        deltaStep.run(true, true);
        cout << endl;
    }


    return 0;
}
