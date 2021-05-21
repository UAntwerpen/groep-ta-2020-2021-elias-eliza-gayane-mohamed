#ifndef SO1_DFA_H
#define SO1_DFA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
using namespace std;

struct State {
    string name;
    map<string, State*> transitions;
};

class DFA_eliza {
public:
    string type;
    vector<State*> states;
    State* start_state;
    vector<State*> last_states;
    string alphabet;

    DFA_eliza(const string &file_name);
    void print();
    ~DFA_eliza();
    bool is_start_state(const State* state) const;
    bool is_accepting_state(const State* state) const;
    bool accepts(const string &input);
};

#endif //SO1_DFA_H
