#include <algorithm>
#include "DFA_eliza.h"
<<<<<<< HEAD
#include "../json.hpp"
=======
#include "json.hpp"
>>>>>>> 2928fc898020f8321c3a7af2ca3db45cb65e7160

using json = nlohmann::json;

bool DFA::accepts(const string &input) {
    State* current_state = start_state;
    for(int c = 0; c < input.size(); c++){
        for(pair<string, State*> t : current_state->transitions){
            string s(1, input[c]);
            if(t.first == s){
                current_state = t.second;
            }
        }
        if(c == input.size()-1 && find(last_states.begin(), last_states.end(), current_state) != last_states.end()){
            return true;
        }
    }
    return false;
}

DFA::DFA(const string &file_name) {
    ifstream input_file;
    input_file.open(file_name);
    json j;
    input_file >> j;
    type = j["type"];
    for(const auto& c : j["alphabet"].items()){
        alphabet += c.value();
    }
    for(const auto& s : j["states"].items()){
        auto* state = new State();
        state->name = s.value()["name"];
        states.emplace_back(state);
        if(s.value()["starting"]){
            start_state = state;
        }
        if(s.value()["accepting"]){
            last_states.emplace_back(state);
        }
    }
    for(auto s : states) {
        for (const auto &t : j["transitions"].items()) {
            if(t.value()["from"] == s->name && alphabet.find(t.value()["input"]) != string::npos) {
                auto it = find_if(states.begin(), states.end(),
                                  [&t](const State *st) { return st->name == t.value()["to"]; });
                auto pos = std::distance(states.begin(), it);
                s->transitions.insert(pair<string, State *>(t.value()["input"], states.at(pos)));
            }
        }
    }
}

void DFA::print() {
    json j;
    j["type"] = type;
    for(char c : alphabet){
        string s(1, c);
        j["alphabet"].emplace_back(s);
    }
    for(State* state : states) {
        j["states"].push_back({{"name", state->name},
                               {"starting", is_start_state(state)},
                               {"accepting", is_accepting_state(state)}});
        for(const auto& t : state->transitions){
            j["transitions"].push_back({{"from", state->name}, {"to", t.second->name}, {"input", t.first}});

        }
    }
    cout << setw(4) << j << endl;
}

bool DFA::is_start_state(const State* state) const {
    return state == start_state;
}

bool DFA::is_accepting_state(const State* state) const {
    for(const State* s : last_states){
        if(state == s) return true;
    }
    return false;
}

DFA::~DFA() {
    for(State* state : states){
        delete state;
    }
}
