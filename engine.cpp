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
    vector<const char*> alle_NFAs = {"../NFA/def_NFA.json", "../NFA/for_from_NFA.json", "../NFA/getallen_NFA.json",
                                     "../NFA/return_NFA.json", "../NFA/string_quotes_NFA.json", "../NFA/while_NFA.json",
                                     "../NFA/ascii_NFA.json","../NFA/bool_NFA.json", "../NFA/chr_NFA.json", "../NFA/dict_NFA.json",
                                     "../NFA/else_elif_NFA.json", "../NFA/False_NFA.json","../NFA/float_NFA.json",
                                     "../NFA/if_in_import_NFA.json", "../NFA/int_isinstance_input_NFA.json",
                                     "../NFA/list_len_NFA.json", "../NFA/max_map_NFA.json", "../NFA/ord_open_NFA.json",
                                     "../NFA/print_pow_NFA.json", "../NFA/range_NFA.json", "../NFA/set_str_NFA.json",
                                     "../NFA/True_NFA.json", "../NFA/tuple_NFA.json", "../NFA/comments_NFA.json"};
    /*
    //Safe safe(alle_NFAs);
    //RE re1("if", 'e');
    //RE re2("elif", 'p');
    //RE re3("import", 'e');
    //RE re4("\"(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+A+B+C+D+E+F+G+H+I+J+K+L+M+N+O+P+Q+R+S+T+U+V+W+X+Y+Z+ +-+:)*\"", '5');
    //vector<pair<RE, string>> test_save = {make_pair(re1, "#e07822"), make_pair(re2, "#e07822"), make_pair(re3, "#e07822"),  make_pair(re4, "#72bf45")};;

    //vector<pair<RE, string>> vector_safe = safe.getSafe();
    //vector<pair<RE, string>> vector_safe = test_save;
    vector<pair<DFA, string>> dfa_s;
    for(int i = 0; i < vector_safe.size(); i++) {
        RE regex = vector_safe[i].first;
        string color = vector_safe[i].second;
        ENFA e_nfa = regex.toENFA();
        DFA dfa = e_nfa.toDFA();
        dfa = dfa.minimize();
        dfa_s.push_back(make_pair(dfa, color));
    }
    */
    vector<pair<DFA, string>> dfa_s;
    for(int i = 0; i < alle_NFAs.size(); i++) {
        NFA nfa(alle_NFAs[i]);
        string color = nfa.getColor();
        DFA dfa = nfa.toDFA();
        DFA ze = dfa.minimize();
        cout << boolalpha << (ze == dfa) << endl;
        dfa_s.push_back(make_pair(dfa,color));
    }

    cout << "jeej" << endl;

    /// het parsen van de files
    for(int i = 1; i < argc; i++){
        Parser parser(argv[i]);
        map<int, vector<string>> parsed_file = parser.getParsedFile();

        map<int, vector<pair<string, string>>> text_for_html;
        /// halen de regexen uit de safe
        for(int j = 0; j < parsed_file.size(); j++){ // j is de lijn waaruit we lezen
            for(int k= 0; k < parsed_file[j].size(); k++) {
                string word = parsed_file[j][k];
                bool herkend = false;
                for(int l = 0;  l < dfa_s.size(); l++) {
                    string color = dfa_s[l].second;
                    if (dfa_s[l].first.accepts(word)) {
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
