#ifndef PYDE_HTML_H
#define PYDE_HTML_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

class HTML {
public:
    HTML(const map<int, vector<pair<string, string>>> &text, const char *filename, const vector<string> &alleFiles);

    void make_HTML_file(const map<int, vector<pair<string, string>>> &text, string filename, const vector<string> &alleFiles);

private:
    /**
     * int: lijn waarop de tekst moet staan
     * vector<pair<string,string>>: een vector die bestaat uit een paar van woorden en een kleurcode
     */
    map<int,vector<pair<string,string>>> text;
    const char* filename;
    vector<string> alle_files;
};


#endif //PYDE_HTML_H
