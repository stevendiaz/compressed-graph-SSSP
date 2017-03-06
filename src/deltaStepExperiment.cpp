#include <string>
#include <cstring>
#include "SSSP.h"
#include "Parser.h"

int main(){
    Parser p = Parser();
	CSR csr = p.parseInput();

    int32_t step = 1;
    int32_t increment = INT_MAX/5;
    for(int i = 0; i < 6; ++i){
        cout << "step = " << step + i * increment << endl;
        DeltaStep deltaStep = DeltaStep(csr, step + i * increment, 10);
        deltaStep.run(true, true);
        cout << endl;
    }


    return 0;
}
