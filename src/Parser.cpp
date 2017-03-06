//
// Created by Jia Li on 3/5/17.
//

#include "Parser.h"

vector<string> Parser::split(char* s) {
    char * pch;
    vector<string> ss;
    pch = strtok (s ," ");

    while (pch != NULL) {
        ss.push_back(pch);
        pch = strtok (NULL, " ,.-");
    }
    return ss;
}

int32_t Parser::stoi32(string s){
    return (int32_t)(stoi(s));
}

CSR Parser::parseInput(){
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
//            cout << "put" << endl;
            csr.put(stoi32(line[1]), stoi32(line[2]), stoi32(line[3]));
//            cout << "put successful" << endl;
        }
    }

//    cout << "everything read" << endl;

    return csr;
}