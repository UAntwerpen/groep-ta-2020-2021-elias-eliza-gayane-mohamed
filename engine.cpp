#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cmath>
#include "automata/wrappers/wrapper_DFA.h"
#include "automata/wrappers/wrapper_NFA.h"
#include "automata/wrappers/wrapper_ENFA.h"
#include "automata/wrappers/wrapper_RE.h"
#include "HTML.h"
#include "Parser.h"
#include "Safe.h"

using namespace std;

int main(int argc, char const* argv[]) {

    /// voegen alle files even toe aan een vector voor de html file te genereren.
    vector<string> alle_files;
    for(int i = 1; i < argc; i++) {
        alle_files.push_back(argv[i]);
    }

    /// het opstellen van de safe
    //vector<const char*> alle_NFAs = {"../input/NFA/def_NFA.json", "../input/NFA/for_NFA.json", "../input/NFA/getallen_NFA.json",
    // "../input/NFA/return_NFA.json", "../input/NFA/string_quotes_NFA.json", "../input/NFA/while_NFA.json"};
    //Safe safe(alle_NFAs);
    RE re1("if", 'e');
    RE re2("elif", 'p');
    RE re3("import", 'e');
    RE re4("\"(E+n+t+e+r+ +s+c+o+d+u+m+b+f+i+:)*\"", '5');
    vector<pair<RE, string>> test_save = {make_pair(re1, "#e07822"), make_pair(re2, "#e07822"), make_pair(re3, "#e07822"),  make_pair(re4, "#72bf45")};;


    /// het parsen van de files
    for(int i = 1; i < argc; i++){
        Parser parser(argv[i]);
        map<int, vector<string>> parsed_file = parser.getParsedFile();

        map<int, vector<pair<string, string>>> text_for_html;
        /// halen de regexen uit de safe
        //vector<pair<RE, string>> vector_safe = safe.getSafe();
        vector<pair<RE, string>> vector_safe = test_save;
        for(int j = 0; j < parsed_file.size(); j++){ // j is de lijn waaruit we lezen
            for(int k= 0; k < parsed_file[j].size(); k++) {
                string word = parsed_file[j][k];
                bool herkend = false;
                for(int l = 0;  l < vector_safe.size(); l++) {
                    RE regex = vector_safe[l].first;
                    string color = vector_safe[l].second;
                    ENFA e_nfa = regex.toENFA();
                    DFA dfa = e_nfa.toDFA();
                    if (dfa.accepts(word)) {
                        text_for_html[j].push_back(make_pair(word, color));
                        herkend = true;
                    }
                }
                if(!herkend){
                    text_for_html[j].push_back(make_pair(word, "no_color"));
                }
            }
        }

        /// genereert een html file met van de text
        /// om in de IDE te kunnen switchen naar meerdere files geef je ook een lijst met alle files mee
        HTML html_file(text_for_html, argv[i] ,alle_files);
    }
    return 0;
}
