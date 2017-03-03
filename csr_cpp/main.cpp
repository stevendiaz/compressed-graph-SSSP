//
// Created by Jia Li on 3/2/17.
//

#include <cstring>
#include <string>
#include "Worklist.h"
#include "CSR.h"
#include "SSSP.h"

const int MAX_CHARS_PER_LINE = 512;

// // Credit:
// http://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html
vector<string> split(const string &s, char delim) {
    vector<string> v;
    auto i = 0;
    auto pos = s.find(delim);
    while (pos != string::npos) {
        v.push_back(s.substr(i, pos - i));
        i = ++pos;
        pos = s.find(delim, pos);

        if (pos == string::npos)
            v.push_back(s.substr(i, s.length()));
    }
    return v;
}

int32_t stoi32(string s){
    return (int32_t)(stoi(s));
}

CSR parseInput(){
    //Extract info from first line
    char buffer[MAX_CHARS_PER_LINE];
    cin.getline(buffer, MAX_CHARS_PER_LINE);
    vector<string> line = split(buffer, ' ');
    int32_t size = stoi32(line[2]);
    int32_t edges = stoi32((line[3]));

    cout << "size = " << size << ", edges = " << edges << endl;

    //Construct CSR as we read the file
    CSR csr = CSR(size);
    // cout << "sad face" <<endl;
    for(int i = 0; i < edges; ++i){
        cin.getline(buffer, MAX_CHARS_PER_LINE);
        line = split(buffer, ' ');
        if(line[0] == "a") {
            csr.put(stoi32(line[1]), stoi32(line[2]), stoi32(line[3]));
        }
    }

    cout << "about to return" << endl;
    return csr;
}


int main(){
    CSR csr = parseInput();

    cout << "hi about to call DEALSTEP" << endl;
    DeltaStep deltaStep = DeltaStep(csr, 1);
    cout  << "construction successful" << endl;
    deltaStep.run();

    return 0;
}
