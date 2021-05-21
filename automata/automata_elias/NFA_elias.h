#ifndef UNTITLED6_NFA_H
#define UNTITLED6_NFA_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "../../json.hpp"
#include "DFA_elias.h"

using namespace std;

using json = nlohmann::json;

class NFA{
private:
    string Color;
    string type;
    string inputfile;
    map<string,vector<vector<string>>> transitie_tabel;
    vector<vector<string>> transitions;
    vector<string> alphabet;
    vector<string> states;
    string start_state;
    vector<string> final_states;


    void maak_transitie_tabel(vector<vector<string>> transitions);
    void readfile(string);
    vector<string> go_to(string current_state,string s);
    bool isgeldig(string s); // kijkt of de inputstring geldig is.
    bool isStartState(string state);
    bool isFinalState(string state);
    bool hasTransitionon(string state,string transitie);
    vector<string> DFAtransitions(string state, vector<string> &DFA_states,vector<string> &final_states, string alphabet, bool &deadstate);

public:

    NFA(const string &inputfile);
    bool accepts(string s);
    void print();
    void print_tabel(); // Dit is een methode voor mezelf om de NFA in tabelvorm weer te geven
    DFA_elias toDFA();

    const string &getColor() const;
};

#endif //UNTITLED6_NFA_H
