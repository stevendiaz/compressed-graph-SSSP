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
    DeltaStep deltaStep = DeltaStep(csr, INT_MAX, 10);
    deltaStep.run(false, true);

    cout << "Random seed: 20" << endl;
    deltaStep = DeltaStep(csr, INT_MAX, 20);
    deltaStep.run(false, true);

    cout << "Random seed: 50" << endl;
    deltaStep = DeltaStep(csr, INT_MAX, 50);
    deltaStep.run(false, true);


    return 0;
}