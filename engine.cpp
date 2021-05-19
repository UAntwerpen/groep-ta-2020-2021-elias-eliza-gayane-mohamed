#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cmath>
#include "automata/DFA_elias.h"
#include "automata/RE_elias.h"
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

        RE regex("hallo",'e');
        ENFA enfa = regex.toENFA();
        DFA dfa = enfa.toDFA();

        if(dfa.accepts("word")){
            int lijn = 1;
            text[lijn].push_back(make_pair("word", "no_color"));
        }

        /// dit is nog wat testcode:
        if(i == 1){
            text[1].push_back(make_pair("hallo", "no_color"));
            text[1].push_back(make_pair("ik", "#FAF207"));
            text[1].push_back(make_pair("ben", "no_color"));
            text[1].push_back(make_pair("Elias", "#55FA07"));
            text[2].push_back(make_pair("def", "#ca7531"));
            text[2].push_back(make_pair("functie", "#ffc66d"));
            text[2].push_back(make_pair("(", "no_color"));
            text[2].push_back(make_pair("parameter", "no_color"));
            text[2].push_back(make_pair(")", "no_color"));
            text[2].push_back(make_pair(":", "no_color"));
        }
        if(i == 2) {
            text[1].push_back(make_pair("hallo", "no_color"));
            text[1].push_back(make_pair("ik", "#FAF207"));
            text[1].push_back(make_pair("ben", "no_color"));
            text[1].push_back(make_pair("Eliza", "#07FAED"));
        }
        if(i == 3) {
            text[1].push_back(make_pair("#", "#fcc9a9"));
            text[1].push_back(make_pair("This", "#fcc9a9"));
            text[1].push_back(make_pair("program", "#fcc9a9"));
            text[1].push_back(make_pair("prints", "#fcc9a9"));
            text[1].push_back(make_pair("hello,", "#fcc9a9"));
            text[1].push_back(make_pair("world!", "#fcc9a9"));
            text[2].push_back(make_pair("", "no_color"));
            text[3].push_back(make_pair("print", "#8888c6"));
            text[3].push_back(make_pair("(", "no_color"));
            text[3].push_back(make_pair("\"Hello, world!\"", "#5b7c57"));
            text[3].push_back(make_pair(")", "no_color"));
        }

        // genereert een html file met van de text
        // om in de IDE te kunnen switchen naar meerdere files geef je ook een lijst met alle files mee
        HTML html_file(text, argv[i] ,alle_files);
    }
    return 0;
}
