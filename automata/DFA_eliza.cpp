//Naam: ELiza Gashi     Studentennr: s0194220
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "DFA.h"
#include "json.hpp"

using json = nlohmann::json;

bool DFA::accepts(const string &input) {
    string current_state = start_state;
    for(int c = 0; c < input.size(); c++){
        map<char, string> transition = transitions[current_state];
        for(pair<char, string> i : transition){
            if(i.first == input[c]){
                current_state = i.second;
            }
        }
        if(c == input.size()-1 && find(last_states.begin(), last_states.end(), current_state) != last_states.end()){
            return true;
        }
    }
    return false;
}

DFA::DFA(string file_name) {
    ifstream input_file;
    input_file.open(file_name);
    json j;
    input_file >> j;
    type = j["type"];
    for(const auto& c : j["alphabet"].items()){
        alphabet += c.value();
    }
    for(const auto& s : j["states"].items()){
        states.emplace_back(s.value()["name"]);
        transitions[s.value()["name"]];
        if(s.value()["starting"]){
            start_state = s.value()["name"];
        }
        if(s.value()["accepting"]){
            last_states.emplace_back(s.value()["name"]);
        }
    }
    for(string& s : states) {
        map<char, string> state_info;
        for (const auto &t : j["transitions"].items()) {
            if(t.value()["from"] == s && alphabet.find(t.value()["input"]) != string::npos){
                string input = t.value()["input"];
                state_info[input[0]] = t.value()["to"];
            }
        }
        transitions[s] = state_info;
    }
}

void DFA::print() {
    json j;
    j["type"] = "DFA";
    for(char c : alphabet){
        string s(1, c);
        j["alphabet"].emplace_back(s);
    }
    for(string state : states) {
        j["states"].push_back({{"name", state},
                               {"starting", is_startingstate(state)},
                               {"accepting", is_acceptingstate(state)}});
    }
    for(pair<string, map<char, string>> t : transitions){
        for(pair<char, string> p : t.second){
            string s(1, p.first);
            j["transitions"].push_back({{"from", t.first},
                                        {"to", p.second},
                                        {"input", s}});
        }
    }
    cout << setw(4) << j << endl;
}

bool DFA::is_startingstate(const string& state) const{
    return state == start_state;
}

bool DFA::is_acceptingstate(const string& state) const {
    for(const string& s : last_states){
        if(state == s) return true;
    }
    return false;
}
