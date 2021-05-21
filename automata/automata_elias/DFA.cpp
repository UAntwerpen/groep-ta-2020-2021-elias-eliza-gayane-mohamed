//#include "DFA.h"
//
//using json = nlohmann::json;
//
//DFA::DFA(const vector<State *> &states, State *startState, const vector<State *> &lastStates, const string &alphabet)
//        : states(states), start_state(startState), last_states(lastStates), alphabet(alphabet) {}
//
////State *DFA::getState(State* to_check) {
////    for(State* s : states){
////        if(s == to_check) return s;
////    }
////    return nullptr;
////}
//
//bool DFA::accepts(const string &input) {
//    State* current_state = start_state;
//    for(int c = 0; c < input.size(); c++){
//        for(pair<char, State*> t : current_state->transitions){
//            if(t.first == input[c]){
//                current_state = t.second;
//            }
//        }
//        if(c == input.size()-1 && find(last_states.begin(), last_states.end(), current_state) != last_states.end()){
//            return true;
//        }
//    }
//    return false;
//}
//
//DFA::DFA(const string& file_name) {
//    ifstream input_file;
//    input_file.open(file_name);
//    json j;
//    input_file >> j;
//    for(const auto& c : j["alphabet"].items()){
//        alphabet += c.value();
//    }
//    for(const auto& s : j["states"].items()){
//        auto* state = new State();
//        state->name = s.value()["name"];
//        if(s.value()["starting"]){
//            state->is_starting = true;
//            start_state = state;
//        }
//        if(s.value()["accepting"]){
//            state->is_accepting = true;
//            last_states.emplace_back(state);
//        }
//        states.emplace_back(state);
//    }
//    for(State* s : states) {
//        for (const auto &t : j["transitions"].items()) {
//            if(t.value()["from"] == s->name && alphabet.find(t.value()["input"]) != string::npos){
//                string input = t.value()["input"];
//                for(State* i : states){
//                    if(i->name == t.value()["to"]) s->transitions[input[0]] = i;
//                }
//            }
//        }
//    }
//}
//
//void DFA::print() {
//    json j;
//    j["type"] = "DFA";
//    for(char c : alphabet){
//        string s(1, c);
//        j["alphabet"].emplace_back(s);
//    }
//    for(State* state : states) {
//        j["states"].push_back({{"name", state->name},
//                               {"starting", state->is_startingstate()},
//                               {"accepting", state->is_acceptingstate()}});
//    }
//    for(const State* state : states){
//        for(pair<char, State*> t : state->transitions){
//            string s(1, t.first);
//              j["transitions"].push_back({{"from", state->name},
//                                        {"to", t.second->name},
//                                        {"input", s}});
//        }
//    }
//    cout << setw(4) << j << endl;
//}
//
//bool State::is_startingstate() const {
//    return is_starting;
//}
//
//bool State::is_acceptingstate() const {
//    return is_accepting;
//}
//
//void DFA::createPairs(vector<pair<State*, State*>> &unmarked, const vector<State*> &s) const {
//    for(int i = 0; i < s.size(); i++){
//        for(int j = i + 1; j < s.size(); j++){
//            unmarked.emplace_back(pair<State*, State*>(s[i], s[j]));
//        }
//    }
//}
//
//bool DFA::areDistinguishable(const State* state1, const State* state2) const {
//    if(is_acceptingstate(state1) && is_acceptingstate(state2)) return false;
//    else if(is_acceptingstate(state1) || is_acceptingstate(state2)) return true;
//    return false;
//}
//
//vector<pair<State*, State*>>::const_iterator DFA::findPair(const vector<pair<State*, State*>> &v, const pair<State*, State*> &p) const {
//    pair<State*, State*> swapped(p.second, p.first);
//    for(int i = 0; i < v.size(); i++){
//        if(v[i] == p || v[i] == swapped){
//            return v.begin() + i;
//        }
//    }
//    return v.end();
//}
//
//void DFA::markPair(vector<pair<State*, State*>> &mark, vector<pair<State*, State*>> &unmark, const pair<State*, State*> &p) const {
//    mark.emplace_back(p);
//    auto it = findPair(unmark, p);
//    if(it != unmark.end()) unmark.erase(it);
//}
//
//vector<pair<State*, State*>> DFA::findMatchingPairs(const pair<State*, State*> &mark,  char c) const {
//    vector<pair<State*, State*>> cur_input;
//    for (State* state : states) {
//        auto it = state->transitions.find(c);
//        if (it->second == mark.first || it->second == mark.second) {
//            cur_input.emplace_back(pair<State*, State*>(state, it->second));
//        }
//    }
//    return cur_input;
//}
//
//vector<pair<State*, State*>> DFA::doTFA(bool compare) {
//    vector<pair<State*, State*>> c_marked;
//    vector<pair<State*, State*>> unmarked;
//    createPairs(unmarked, states);
//    for (int i = 0; i < unmarked.size(); i++) {
//        if (areDistinguishable(unmarked[i].first, unmarked[i].second)) {
//            markPair(c_marked, unmarked, unmarked[i]);
//            i--;
//            if(compare && (unmarked[i].first->is_startingstate() && unmarked[i].second->is_startingstate())){
//                return unmarked;
//            }
//        }
//    }
//    while (!c_marked.empty()) {
//        for (char c : alphabet) {
//            vector<pair<State*, State*>> cur_input = findMatchingPairs(c_marked.front(), c);
//            vector<pair<State*, State*>> check_marked;
//            for (int i = 0; i < cur_input.size(); i++) {
//                for (int j = 0; j < cur_input.size(); j++) {
//                    pair<State*, State*> p(cur_input[i].first, cur_input[j].first);
//                    if (cur_input[i].second != cur_input[j].second && findPair(check_marked, p) == check_marked.end()) {
//                        check_marked.emplace_back(p);
//                    }
//                }
//            }
//            if(!check_marked.empty()){
//                for(const auto& p : check_marked){
//                    if(findPair(c_marked, p) == c_marked.end() && findPair(marked, p) == marked.end()){
//                        markPair(c_marked, unmarked, p);
//                        if(compare && (p.first->is_startingstate() && p.second->is_startingstate())){
//                            return unmarked;
//                        }
//                    }
//                }
//            }
//            if(c == alphabet.back()) {
//                marked.emplace_back(c_marked.front());
//                c_marked.erase(c_marked.begin());
//            }
//        }
//    }
//    return unmarked;
//}
//
// DFA DFA::minimize() {
//    DFA minDFA(states, start_state, last_states, alphabet);
//    vector<pair<State*,State*>> unmarked = minDFA.doTFA(false);
//    marked = minDFA.marked;
//    createMinDFA(unmarked, minDFA);
//    return minDFA;
//}
//
//void DFA::createMinDFA(const vector<pair<State*, State*>> &unmarked, DFA &dfa) {
//    vector<set<State*>> new_states;
//    for(int i = 0; i < unmarked.size(); i++){
//        set<State*> state = {unmarked[i].first, unmarked[i].second};
//        for(int j = i + 1; j < unmarked.size(); j++){
//            if(state.find(unmarked[j].first) != state.end() || state.find(unmarked[j].second) != state.end()){
//                state.insert(unmarked[j].first);
//                state.insert(unmarked[j].second);
//                i++;
//            }
//        }
//        new_states.emplace_back(state);
//    }
//    createMinStates(new_states, dfa);
//    createMinTransitions(dfa);
//}
//
//void DFA::createMinStates(const vector<set<State*>> &new_states, DFA &dfa) const {
//    for(int i = 0; i < dfa.states.size(); i++){
//        for(const auto &j : new_states){
//            if(j.count(dfa.states[i]) != 0){
//                dfa.states.erase(dfa.states.begin() + i);
//                i--;
//            }
//        }
//    }
//    for(int i = 0; i < dfa.states.size(); i++){
//        if(!dfa.states[i]->is_acceptingstate() && !dfa.states[i]->is_startingstate()){
//            dfa.states.erase(dfa.states.begin() + i);
//            i--;
//        }
//    }
//    for(const auto &i : new_states){
//        string new_state;
//        for(const auto &j : i){
//            new_state += j->name;
//        }
//        sort(new_state.begin(), new_state.end());
//        State* result;
//        for(char c : new_state) {
//            result->name += c;
//            result->name += ", ";
//        }
//        dfa.states.emplace_back(result);
//    }
//    for(const auto &state : dfa.states){
//        if(state->name.find(dfa.start_state->name) != string::npos){
//            dfa.start_state = state;
//        }
//        for(int s = 0; s < dfa.last_states.size(); s++){
//            if(state->name.find(dfa.last_states[s]->name) != string::npos){
//                dfa.last_states.erase(dfa.last_states.begin() + s);
//                dfa.last_states.emplace_back(state);
//            }
//        }
//    }
//    formatStates(dfa);
//}
//
//void DFA::formatStates(DFA &dfa) const {
//    for(State* state : dfa.states){
//        if(state->name.back() == ' '){
//            state->name = state->name.substr(0, state->name.size() - 2);
//        }
//        state->name.insert(state->name.begin(), '{');
//        state->name += '}';
//    }
//    for(State* lstate : dfa.last_states){
//        if(lstate->name.back() == ' '){
//            lstate->name = lstate->name.substr(0, lstate->name.size() - 2);
//        }
//        lstate->name.insert(lstate->name.begin(), '{');
//        lstate->name += '}';
//    }
//    dfa.start_state->name.insert(dfa.start_state->name.begin(), '{');
//    if(dfa.start_state->name.back() == ' '){
//        dfa.start_state->name = dfa.start_state->name.substr(0, dfa.start_state->name.size() - 2);
//    }
//    dfa.start_state->name += '}';
//}
//
//void DFA::createMinTransitions(DFA &dfa) const {
////    pair<char, State*>  n_transitions;
////    for(State* state : dfa.states) {
////        for(pair<char, State*> transition : state->transitions){
////            if(state->name.find(transition.second->name) != string::npos){
////                state.s = state;
////                n_transitions[transition.first] = transition.second;
////            }
////        }
////    }
////    for(auto &transition : n_transitions){
////        for (const string &state : dfa.states) {
////            for(const auto& t : transition.second) {
////                if(state.find(t.second) != string::npos){
////                    transition.second.at(t.first) = state;
////                }
////            }
////        }
////    }
////    dfa.transitions = n_transitions;
//}
//
//void DFA::printTable() {
//    sort(states.begin(), states.end());
//    for (int i = 1; i < states.size(); i++) {
//        cout << states[i] << '\t';
//        for (int j = 0; j < i; j++) {
//            pair<State*, State*> p(states[i], states[j]);
//            if(findPair(marked, p) != marked.end()){
//                cout << "X" << '\t';
//            } else cout << "-" << '\t';
//        }
//        cout << endl;
//    }
//    for (int i = 0; i < states.size()-1; i++) {
//        cout << '\t' + states[i];
//    }
//    cout << endl;
//}
//
//bool operator==(const DFA &dfa1, const DFA &dfa2) {
//    DFA TFA = dfa1;
//    move(begin(dfa2.states), end(dfa2.states), back_inserter(TFA.states));
//    move(begin(dfa2.last_states), end(dfa2.last_states), back_inserter(TFA.last_states));
//    for(State* state : dfa2.states){
//        for(const auto &t : state->transitions){
//
//        }
//    }
//    for(const auto &t : dfa2.transitions) {
//        TFA.transitions[t.first] = t.second;
//    }
//    vector<pair<State*, State*>> unmarked = TFA.doTFA(true);
//    TFA.printTable();
//    for(const auto &p : unmarked){
//        if((TFA.is_startingstate(p.first) && dfa2.is_startingstate(p.second)) || (TFA.is_startingstate(p.second) && dfa2.is_startingstate(p.first))){
//            return true;
//        }
//    }
//    return false;
//}
