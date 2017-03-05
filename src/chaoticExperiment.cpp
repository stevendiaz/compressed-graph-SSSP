#include <string>
#include <cstring>
#include "SSSP.h"
#include "CSR.h"

const int MAX_CHARS_PER_LINE = 512;

vector<string> split(char* s) {
    char * pch;
    vector<string> ss;
    pch = strtok (s ," ");

    while (pch != NULL) {
        ss.push_back(pch);
        pch = strtok (NULL, " ,.-");
    }
    return ss;
}

int32_t stoi32(string s){
    return (int32_t)(stoi(s));
}

CSR parseInput(){
    //Extract info from first line
    char buffer[MAX_CHARS_PER_LINE];
    cin.getline(buffer, MAX_CHARS_PER_LINE);
    vector<string> line = split(buffer);
    int32_t size = stoi32(line[2]);
    int32_t edges = stoi32((line[3]));

    //Construct CSR as we read the file
    CSR csr = CSR(size);
    for(int i = 0; i < edges; ++i){
        cin.getline(buffer, MAX_CHARS_PER_LINE);
        line = split(buffer);
        if(line[0] == "a") {
            csr.put(stoi32(line[1]), stoi32(line[2]), stoi32(line[3]));
        }
    }

    return csr;
}


int main(){
    CSR csr = parseInput();

    cout << "Random seed: 10" << endl;
    clock_t t;
    DeltaStep deltaStep = DeltaStep(csr, INT_MAX, 10);
    deltaStep.run(false, true);
    t = clock() - t;
    cout << "Delta step algorithm with choatic relaxation took " << ((float)t)/CLOCKS_PER_SEC << " seconds" << endl; 

    cout << "Random seed: 20" << endl;
    clock_t x;
    deltaStep = DeltaStep(csr, INT_MAX, 20);
    deltaStep.run(false, true);
    x = clock() - x;
    cout << "Delta step algorithm with choatic relaxation took " << ((float)x)/CLOCKS_PER_SEC << " seconds" << endl; 

    cout << "Random seed: 50" << endl;
    clock_t y;
    deltaStep = DeltaStep(csr, INT_MAX, 50);
    deltaStep.run(false, true);
    y = clock() - y;
    cout << "Delta step algorithm with choatic relaxation took " << ((float)y)/CLOCKS_PER_SEC << " seconds" << endl; 


    return 0;
}
