#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstring>

//My includes
#include <vector>
#include <sstream>
#include <stdlib.h>

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int main() {
    ifstream infile; 
    std::string line;
    infile.open("data.txt");
    while(!infile.eof()) {
        std::getline(infile, line);
        if (line[0] == 'c') {
            cout << "COMMENT" << std::endl;
        }
        else if (line[0] == 'p') {
            cout << "PROBLEM LINE" << std::endl;
        }
        else {
            std::vector<std::string> delimited = split(line, ' ');
            std::string edge_desc = delimited[0];
            int a = atoi(delimited[1].c_str());
            int b = atoi(delimited[2].c_str());
            int w = atoi(delimited[3].c_str());
            cout << "edge description: " << edge_desc << " a: " << a << " b: " << b << " w: " << w << std::endl;
        }
    }
    infile.close();
    return 0;
}

int not_main()
{
  // create a file-reading object
  ifstream fin;
  fin.open("data.txt"); // open a file
  if (!fin.good()) 
    return 1; // exit if file not found

  // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);

    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index

    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0

    // parse the line
    token[0] = strtok(buf, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        token[n] = strtok(0, DELIMITER); // subsequent tokens
        if (!token[n]) break; // no more tokens
      }
    }

    // process (print) the tokens
    for (int i = 0; i < n; i++) // n = #of tokens
      cout << "Token[" << i << "] = " << token[i] << endl;
    cout << endl;
  }
}
