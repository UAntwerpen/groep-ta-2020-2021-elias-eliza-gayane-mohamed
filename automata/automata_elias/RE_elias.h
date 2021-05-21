#ifndef UNTITLED6_RE_H
#define UNTITLED6_RE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "../../json.hpp"
#include "ENFA_elias.h"

using namespace std;


struct node{
    node(bool starthaakje, bool eindhaakje, bool start, bool final,
         char transitionSymbol, node *left, node *right, node *prev, int nummer);

    bool starthaakje;
    bool eindhaakje;
    bool start;
    bool final;
    char transition_symbol;
    node* left = nullptr;
    node* right = nullptr;
    node* prev = nullptr;
    int nummer;
};

class RE_elias {
public:
    RE_elias(const string &regex, char epsilon);

    ENFA_elias toENFA();

private:
    void make_transitions();
    void print(node* current, vector<int> staten);
    node* regextree;
    string regex;
    char epsilon;
    int aantal_states;

};


#endif //UNTITLED6_RE_H
