#include <string>
#include <cstring>
#include "SSSP.h"
#include "Parser.h"

int main(){
    Parser p = Parser();
	CSR csr = p.parseInput();

    for(int i = 1; i < 120; i+=10){
        cout << "step = " << i << endl;
        DeltaStep deltaStep = DeltaStep(csr, i, 10);
        deltaStep.run(true, true);
        cout << endl;
    }


    return 0;
}
