#ifndef PYDE_WRAPPER_DFA_H
#define PYDE_WRAPPER_DFA_H
#include "../automata_elias/DFA_elias.h"
#include "../automata_eliza/DFA_eliza.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "../../json.hpp"

using namespace std;

class DFA {
private:
    DFA_elias dfaElias;
    DFA_eliza dfaEliza;

public:

    DFA(const DFA_elias &dfaElias);

    DFA(const string &inputfile);

    bool accepts(string s);
    void print();
    void printTable();

    bool operator == (const DFA &other);

    DFA minimize();
};


#endif //PYDE_WRAPPER_DFA_H
