
#ifndef UNTITLED6_DFA_H
#define UNTITLED6_DFA_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "../../json.hpp"

using namespace std;

using json = nlohmann::json;

class DFA_elias{
private:

    string type;
    string inputfile;
    map<string,vector<vector<string>>> transitie_tabel;
    vector<vector<string>> transitions;
    vector<string> alphabet;
    vector<string> states;
    string start_state;
    vector<string> final_states;
    vector<vector<string>> minimized_tabel;


    void maak_transitie_tabel(vector<vector<string>> transitions);
    void readfile(string);
    string go_to(vector<vector<string>> transitions, string current_state,string s);
    bool isgeldig(string s); // kijkt of de inputstring geldig is.
    bool isStartState(string state);
    bool isFinalState(vector<string> final_states,string state);
    vector<vector<string>> table_filling_algoritme(vector<vector<string>>transitions, vector<string> final_states, vector<string> states, vector<vector<string>> &minimized); // methode die het table filling algoritme uitvoert
    vector<string> DFAtransitions(vector<string> newDFAstates,string from, vector<string> &DFA_states, string alphabet); // methode die de nieuwe DFA_elias transities bepaald

public:

    DFA_elias(const string &inputfile);

    DFA_elias(const string &type, const vector<vector<string>> &transitions, const vector<string> &alphabet,
              const vector<string> &states, const string &startState, const vector<string> &finalStates);

    bool accepts(string s);
    void print();
    void print_tabel(); // Dit is een methode voor mezelf om de NFA_elias in tabelvorm weer te geven
    void printTable();

    bool operator == (const DFA_elias &other);

    DFA_elias minimize();

};


#endif //UNTITLED6_DFA_H
