#include "wrapper_NFA.h"

#include <utility>

NFA::NFA(const string &inputfile){
    NFA_elias nfa_(inputfile);
    nfa = nfa_;
}

bool NFA::accepts(string s){
    return nfa.accepts(s);
}

void NFA::print(){
    nfa.print();
}

DFA NFA::toDFA(){
    DFA_elias dfaElias = nfa.toDFA();
    DFA _dfa(dfaElias);
    return _dfa;
}


const string &NFA::getColor() const{
    return nfa.getColor();
}