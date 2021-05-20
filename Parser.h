#ifndef PYDE_PARSER_H
#define PYDE_PARSER_H

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Parser {
public:
    Parser(const char *filename);
    vector<string> split_line(string &s, char d);

    const map<int, vector<string>> &getParsedFile() const;


private:
    map<int, string> line_list;
    map<int, vector<string> > parsed_file;
};


#endif //PYDE_PARSER_H
