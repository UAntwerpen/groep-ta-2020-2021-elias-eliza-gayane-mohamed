#include "Safe.h"

Safe::Safe(const vector<const char *> &nfAs) : NFAs(nfAs) {
    safe = {};
    make_safe(NFAs);
}

void Safe::make_safe(vector<const char *> NFAs){
    for(int i = 0; i < NFAs.size(); i++){
        cout << NFAs[i] << endl;
        NFA nfa(NFAs[i]);
        string color = nfa.getColor();
        ofstream elias_dfa;
        DFA dfa = nfa.toDFA();
        //RE re = dfa.toRe();
        RE re("fdfdsd", 'e');
        safe.push_back(make_pair(re,color));
    }
}

const vector<pair<RE, string>> &Safe::getSafe() const {
    return safe;
}

