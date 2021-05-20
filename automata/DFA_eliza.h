//Naam: ELiza Gashi     Studentennr: s0194220
#ifndef SO1_DFA_H
#define SO1_DFA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
using namespace std;

class DFA{
public:
    string type;
    vector<string> states;  //Set of states
    string start_state;   //First state
    vector<string> last_states;   //last state
    map<string, map<char, string>> transitions;
    string alphabet; //input symbols

    DFA(string file_name);
    void print();
    bool accepts(const string &input);
    bool is_startingstate(const string& state) const;
    bool is_acceptingstate(const string& state) const;
};

#endif //SO1_DFA_H
