#ifndef PYDE_PYTHON_H
#define PYDE_PYTHON_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

enum ColorEnum {Indigo, Orange, Grey, Green, Yellow, Blue, NoColor};

class ColorScheme {
public:
    ColorScheme(const char *filename);
    void make_color_scheme();
    vector<string> split_line(string &s, char d);
    ColorEnum matchColor(const string &s, string &sstring);

private:
    map<int, string> line_list;
    map<int, vector<pair<string, string>>> colored_words;
    map<ColorEnum, vector<string>> used_words = {{Indigo, {"bool", "float", "int", "str", "tuple", "set", "list", "dict", "isinstance",
                                                  "print", "chr", "ord", "max", "map", "range", "input", "len", "pow", "open", "ascii"}},
                                              {Orange, {"def", "return", "for", "while", "in", "if", "else", "elif" }},
                                              {Yellow, {"import", "True", "False", "from" }}};
};
#endif //PYDE_PYTHON_H
