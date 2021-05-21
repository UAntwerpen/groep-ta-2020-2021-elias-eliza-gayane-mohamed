#include "wrapper_ENFA.h"

ENFA::ENFA(const string &inputfile){
    ENFA_elias enfaElias__(inputfile);
    enfaElias = enfaElias__;
}

bool ENFA::accepts(string s){
    return enfaElias.accepts(s);
}

void ENFA::print(){
    enfaElias.print();
}

DFA ENFA::toDFA(){
    DFA_elias dfa = enfaElias.toDFA();
    DFA return_dfa(dfa);
    return return_dfa;
}

const string &ENFA::getColor() const{
    return enfaElias.getColor();
}

ENFA::ENFA(const ENFA_elias &enfaElias) : enfaElias(enfaElias) {}
