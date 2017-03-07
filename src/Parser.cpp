//
// Created by Jia Li on 3/5/17.
//

#include "Parser.h"

CSR Parser::parseInput(){
    //Extract info from first line
    string s;
    int32_t size, edges, x, y, val;
    cin >> s >> s >> size >> edges;

    cout << "size = " << size << ", edges = " << edges << endl;

    //Construct CSR as we read the file
    CSR csr = CSR(size);
    for(int i = 0; i < edges; ++i){
        cin >> s >> x >> y >> val;
        if(s == "a") {
            csr.put(x, y, val);
        }
    }
    csr.update(x);

    return csr;
}