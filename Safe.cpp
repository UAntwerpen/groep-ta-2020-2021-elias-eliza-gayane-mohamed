#include "Safe.h"

Safe::Safe(const vector<const char *> &nfAs) : NFAs(nfAs) {
    safe = {};
    make_safe(NFAs);
}

void Safe::make_safe(vector<const char *> NFAs){
    for(int i = 1; i < NFAs.size(); i++){
        NFA nfa(NFAs[i]);
        string color = nfa.getColor();
        DFA dfa = nfa.toDFA();
        //RE re = dfa.toRE(); // methode moet nog gemaakt worden
        RE re("voorbeeld",'d');
        safe.push_back(make_pair(re,color));
    }
}

const vector<pair<RE, string>> &Safe::getSafe() const {
    return safe;
}

