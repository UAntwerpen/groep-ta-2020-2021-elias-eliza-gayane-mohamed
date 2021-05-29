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

using namespace std;

int main(int argc, char const* argv[]) {

    /// voegen alle files even toe aan een vector voor de html file te genereren.
    vector<string> alle_files;
    for(int i = 1; i < argc; i++) {
        alle_files.push_back(argv[i]);
    }

    /// het opstellen van de safe
    vector<const char*> alle_NFAs = {"../NFA/def_NFA.json",
                                     "../NFA/for_from_NFA.json",
                                     "../NFA/return_NFA.json",
                                     "../NFA/while_NFA.json",
                                     "../NFA/ascii_NFA.json",
                                     "../NFA/bool_NFA.json",
                                     "../NFA/chr_NFA.json",
                                     "../NFA/dict_NFA.json",
                                     "../NFA/else_elif_NFA.json",
                                     "../NFA/False_NFA.json",
                                     "../NFA/float_NFA.json",
                                     "../NFA/if_in_import_NFA.json",
                                     "../NFA/int_isinstance_input_NFA.json",
                                     "../NFA/list_len_NFA.json",
                                     "../NFA/max_map_NFA.json",
                                     "../NFA/ord_open_NFA.json",
                                     "../NFA/print_pow_NFA.json",
                                     "../NFA/range_NFA.json",
                                     "../NFA/set_str_NFA.json",
                                     "../NFA/True_NFA.json",
                                     "../NFA/tuple_NFA.json",
                                     "../NFA/getallen_NFA.json",
                                     "../NFA/string_quotes_NFA.json",
                                     "../NFA/comments_NFA.json"};

    RE re1("def", 'E');
    RE re2("f(or+rom)", 'E');
    RE re3("return", 'E');
    RE re4("while", 'E');
    RE re5("ascii", 'E');
    RE re6("bool", 'E');
    RE re7("chr", 'E');
    RE re8("dict",'E');
    RE re9("el(if+se)", 'E');
    RE re10("False", 'E');
    RE re11("float", 'E');
    RE re12("i(sinstance+nt+nput)", 'E');
    RE re13("l(ist+en)", 'E');
    RE re14("ma(x+p)", 'E');
    RE re15("o(rd+pen)", 'E');
    RE re16("p(rint+ow)", 'E');
    RE re17("range", 'E');
    RE re18("s(et+tr)", 'E');
    RE re19("True", 'E');
    RE re20("tuple", 'E');
    RE re21("(0+1+2+3+4+5+6+7+8+9)*(E+.)(0+1+2+3+4+5+6+7+8+9)*", 'E');
    vector<pair<RE, string>> test_save = {make_pair(re1, "#e07822"),
                                          make_pair(re2, "#e07822"),
                                          make_pair(re3, "#e07822"),
                                          make_pair(re4, "#e07822"),
                                          make_pair(re5, "#e07822"),
                                          make_pair(re6, "#e07822"),
                                          make_pair(re7, "#e07822"),
                                          make_pair(re8, "#e07822"),
                                          make_pair(re9, "#e07822"),
                                          make_pair(re10, "#e07822"),
                                          make_pair(re11, "#e07822"),
                                          make_pair(re12, "#e07822"),
                                          make_pair(re13, "#e07822"),
                                          make_pair(re14, "#e07822"),
                                          make_pair(re15, "#e07822"),
                                          make_pair(re16, "#e07822"),
                                          make_pair(re17, "#e07822"),
                                          make_pair(re18, "#e07822"),
                                          make_pair(re19, "#e07822"),
                                          make_pair(re20, "#e07822"),
                                          make_pair(re21, "#e07822")};

    vector<pair<DFA, string>> vergelijk_dfa_s;
    for(int i = 0; i < test_save.size(); i++) {
        RE regex = test_save[i].first;
        string color = test_save[i].second;
        ENFA e_nfa = regex.toENFA();
        DFA dfa = e_nfa.toDFA();
        dfa = dfa.minimize();
        vergelijk_dfa_s.push_back(make_pair(dfa, color));
    }

    vector<pair<DFA, string>> dfa_s;
    for(int i = 0; i < alle_NFAs.size(); i++) {
        NFA nfa(alle_NFAs[i]);
        string color = nfa.getColor();
        DFA dfa = nfa.toDFA();
        dfa.minimize();
        if(i < vergelijk_dfa_s.size()){
            cout << i << endl;
            if(vergelijk_dfa_s[i].first == dfa){
                cout << "--------------juist----------------" << endl;
                dfa_s.push_back(make_pair(dfa,color));
            }
            else{
                cout << "--------------false----------------" << endl;
            }
        }
        else{
            cout << i << endl;
            dfa_s.push_back(make_pair(dfa,color));
        }
    }

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
