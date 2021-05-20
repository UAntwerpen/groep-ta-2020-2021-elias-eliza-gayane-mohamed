#ifndef PYDE_SAFE_H
#define PYDE_SAFE_H

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "automata/NFA_elias.h"
#include "automata/DFA_elias.h"
#include "automata/RE_elias.h"

using namespace std;

class Safe {
public:
    Safe(const vector<const char *> &nfAs);

    void make_safe(vector<const char *> NFAs);

    const vector<pair<RE, string>> &getSafe() const;

private:
    vector<const char *> NFAs;
    vector<pair< RE, string>> safe; // vector<pair< "regex", "color" >>
};


#endif //PYDE_SAFE_H