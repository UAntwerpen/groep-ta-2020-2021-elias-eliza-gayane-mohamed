//#ifndef SO1_DFA_H
//#define SO1_DFA_H
//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <map>
//#include <iomanip>
//#include <set>
//#include <fstream>
//#include "json.hpp"
//
//using namespace std;
//
//struct State{
//    string name;
//    bool is_starting = false;
//    bool is_accepting = false;
//    map<char, State*> transitions;
//
//    bool is_startingstate() const;    //DONE
//    bool is_acceptingstate() const;    //DONE
//};
//
//class DFA{
//    vector<pair<State*, State*>> marked;
//
//    void createMinDFA(const vector<pair<State*, State*>> &unmarked, DFA &dfa);     //DONE
//    void createMinStates(const vector<set<State*>> &new_states, DFA &dfa) const;    //DONE
//    void formatStates(DFA &dfa) const;      //DONE
//    void createMinTransitions(DFA &dfa) const;
//    void createPairs(vector<pair<State*, State*>> &unmarked, const vector<State*> &s) const;     //DONE
//    bool areDistinguishable(const State* state1, const State* state2) const;     //DONE
//    vector<pair<State*,State*>> findMatchingPairs(const pair<State*, State*> &mark, char c) const;     //DONE
//    void markPair(vector<pair<State*, State*>> &mark, vector<pair<State*, State*>> &unmark, const pair<State*, State*> &p) const;     //DONE
//    vector<pair<State*, State*>>::const_iterator findPair(const vector<pair<State*, State*>> &v, const pair<State*, State*> &p) const;     //DONE
//
//public:
//    vector<State*> states;
//    State* start_state;
//    vector<State*> last_states;
//    string alphabet;
//
//    DFA(const string& file_name);    //DONE
//    DFA(const vector<State *> &states, State *startState, const vector<State *> &lastStates, const string &alphabet);    //DONE
//    void print();    //DONE
//    bool accepts(const string &input);    //DONE
//
////    State* getState(State* to_check);
//
//    DFA minimize();     //DONE
//    void printTable();
//    vector<pair<State*, State*>> doTFA(bool compare);    //DONE
//};
//
//
//bool operator==(const DFA &dfa1, const DFA &dfa2);
//
//#endif
