#ifndef PYDE_WRAPPER_ENFA_H
#define PYDE_WRAPPER_ENFA_H

#include "../../automata/automata_elias/ENFA_elias.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "../../json.hpp"
#include "wrapper_DFA.h"

using namespace std;

class ENFA {
private:
    ENFA_elias enfaElias;

public:

    ENFA(const string &inputfile);

    ENFA(const ENFA_elias &enfaElias);

    bool accepts(string s);
    void print();
    DFA toDFA();

    const string &getColor() const;
};


#endif //PYDE_WRAPPER_ENFA_H
