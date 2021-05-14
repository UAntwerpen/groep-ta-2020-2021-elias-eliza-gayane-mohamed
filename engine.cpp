#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cmath>
#include "automata/DFA_elias.h"
#include "HTML.h"

using namespace std;

int main(int argc, char const* argv[]) {

    vector<string> alle_files;
    for(int i = 1; i < argc; i++) {
        alle_files.push_back(argv[i]);
    }

    for(int i = 1; i < argc; i++){
        ifstream txt_file;
        txt_file.open(argv[i]);
        string line;
        if (txt_file.is_open()) {
            while (getline(txt_file, line)) {
                cout << line << endl;
            }
        }
        txt_file.close();
        map<int, vector<pair<string, string>>> text;
        text[1].push_back(make_pair("hallo", "no_color"));
        text[1].push_back(make_pair("ik", "#FAF207"));
        text[1].push_back(make_pair("ben", "no_color"));
        text[1].push_back(make_pair("elias", "#55FA07"));
        text[2].push_back(make_pair("hallo", "no_color"));
        text[2].push_back(make_pair("ik", "#FAF207"));
        text[2].push_back(make_pair("ben", "no_color"));
        text[2].push_back(make_pair("Eliza", "#07FAED"));

        // genereert een html file met van de text
        // om in de IDE te kunnen switchen naar meerdere files geef je ook een lijst met alle files mee
        HTML html_file(text, argv[i] ,alle_files);
    }
    return 0;
}
