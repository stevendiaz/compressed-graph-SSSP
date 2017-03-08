//
// Created by Jia Li on 3/5/17.
//

#ifndef ASSIGNMENT3_PERFORMANCEPROGRAMMING_PARSER_H
#define ASSIGNMENT3_PERFORMANCEPROGRAMMING_PARSER_H

#include <string>
#include <cstring>
#include <vector>
#include <cstdint>
#include "CSR.h"

const int MAX_CHARS_PER_LINE = 512;

using namespace std;

class Parser{
private:
    int32_t src;
    vector<string> split(char* s);
    int32_t stoi32(string s);
public:
    Parser(int32_t sourceNode);
    CSR parseInput();
};

#endif //ASSIGNMENT3_PERFORMANCEPROGRAMMING_PARSER_H
