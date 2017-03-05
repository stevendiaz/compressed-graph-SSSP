#include <string>
#include <cstring>
#include "SSSP.h"
#include "Parser.h"

int main(){
    Parser p = Parser();
	CSR csr = p.parseInput();

    int32_t step = INT_MAX/5;
    for(int i = 1; i <= INT_MAX; i += step){
        cout << "step = " << i << endl;
        DeltaStep deltaStep = DeltaStep(csr, i, 10);
        deltaStep.run(true, true);
    } 


    return 0;
}
