#ifndef UNTITLED6_ENFA_H
#define UNTITLED6_ENFA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "../json.hpp"
#include "DFA_elias.h"

using namespace std;

using json = nlohmann::json;

class ENFA{
private:
    string type;
    string eplsilontransitie;
    vector<string> alphabet;
    vector<string> states;
    string start_state;
    vector<string> final_states;
    vector<vector<string>> transitions;
    string inputfile;
    map<string,vector<vector<string>>> transitie_tabel;


    void maak_transitie_tabel(vector<vector<string>> transitions);
    void readfile(string);
    vector<string> go_to(string current_state,string s);
    bool isgeldig(string s); // kijkt of de inputstring geldig is.
    bool isStartState(string state);
    bool isFinalState(string state);
    bool hasTransitionon(string state,string transitie);
    vector<string> DFAtransitions(string state, vector<string> &DFA_states,vector<string> &final_states, string alphabet, bool &deadstate);
    vector<string> get_closure(string startstate);

public:

    ENFA(const string &inputfile);

    ENFA(const string &type, const string &eplsilontransitie, const vector<string> &alphabet,
         const vector<string> &states, const string &startState, const vector<string> &finalStates,
         const vector<vector<string>> &transitions);

    bool accepts(string s);
    void print();
    void print_tabel(); // Dit is een methode voor mezelf om de ENFA in tabelvorm weer te geven
    DFA toDFA();
};
#endif //UNTITLED6_ENFA_H
