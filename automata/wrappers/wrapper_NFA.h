#ifndef PYDE_WRAPPER_NFA_H
#define PYDE_WRAPPER_NFA_H

#include "../../automata/automata_elias/NFA_elias.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "../../json.hpp"
#include "wrapper_DFA.h"

using namespace std;

class NFA {
private:
    NFA_elias nfa;

public:
    NFA (const string &inputfile);
    bool accepts(string s);
    void print();
    DFA toDFA();

    const string &getColor() const;
};


#endif //PYDE_WRAPPER_NFA_H
