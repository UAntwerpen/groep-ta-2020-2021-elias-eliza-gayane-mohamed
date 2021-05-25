#include "wrapper_DFA.h"

DFA::DFA(const string &inputfile){
    DFA_elias DFA_(inputfile);
    dfaElias = DFA_;
    DFA_eliza DFA__(inputfile);
    dfaEliza = DFA__;
}

bool DFA::accepts(string s){
    return dfaElias.accepts(s);
}

void DFA::print(){
    dfaElias.print();
}

void DFA::printTable(){
    dfaElias.printTable();
}

bool DFA::operator == (const DFA &other){
    return dfaElias == other.dfaElias;
}

DFA DFA::minimize(){
    DFA_elias minimize_dfa = dfaElias;
    minimize_dfa.minimize();
    DFA return_dfa(minimize_dfa);
    return return_dfa;
}

DFA::DFA(const DFA_elias &dfaElias) : dfaElias(dfaElias) {}
