
#include "NFA_elias.h"

NFA::NFA(const string &inputfile) : inputfile(inputfile) {

    readfile(inputfile);
}

void NFA::readfile(string){
    ifstream input(inputfile);
    json j;
    input >> j;

    /// We gaan eerst alle componenten van de NFA bepalen de quintuple: {Q,E,§,q0,F}
    type = j["type"];

    Color = j["color"];

    for (int i = 0; i < j["alphabet"].size(); ++i) {
        string name = j["alphabet"][i];
        alphabet.push_back(name);
    }

    for (int i = 0; i < j["states"].size(); ++i) {
        string name = j["states"][i]["name"];
        states.push_back(name);
        sort(states.begin(),states.end());
    }

    for (int i = 0; i < j["transitions"].size(); ++i) {
        vector<string> transition;
        string from = j["transitions"][i]["from"];
        string to = j["transitions"][i]["to"];
        string input = j["transitions"][i]["input"];
        transition.push_back(from);
        transition.push_back(to);
        transition.push_back(input);
        transitions.push_back(transition);
    }

    for (int i = 0; i < j["states"].size(); ++i) {
        bool startstate = j["states"][i]["starting"];
        if(startstate == true){
            start_state = j["states"][i]["name"];
        }
    }

    for (int i = 0; i < j["states"].size(); ++i) {
        bool finalstate = j["states"][i]["accepting"];
        if(finalstate == true){
            final_states.push_back(j["states"][i]["name"]);
        }
    }
    maak_transitie_tabel(transitions);
}

void NFA::maak_transitie_tabel(vector<vector<string>> transitions){
    for (int i = 0; i < states.size(); ++i) {
        vector<vector<string>> overgangen;
        for (int j = 0; j < transitions.size(); ++j){
            if(states[i] == transitions[j][0]){
                //cout << "from:" << transitions[j][0] << " to: " << transitions[j][1] << " over: " << transitions[j][2] << endl;
                vector<string> item;
                item.push_back(transitions[j][1]);
                item.push_back(transitions[j][2]);
                overgangen.push_back(item);
            }
        }
        transitie_tabel[states[i]] = overgangen;
    }
}

vector<string> NFA::go_to(string current_state,string s){
    vector<string> returnwaarde;
    vector<vector<string>> transition = transitie_tabel[current_state];
    for (int i = 0; i < transition.size(); ++i){
        if (transition[i][1] == s){
            returnwaarde.push_back(transition[i][0]);
        }
    }
    return returnwaarde;
}

bool NFA::isgeldig(string s){
    bool foutsymbool = false;
    vector<string> foute_symbolen;
    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < alphabet.size(); ++j) {
            string transition_symbol;
            transition_symbol = s[i];
            if (find(alphabet.begin(),alphabet.end(),transition_symbol) == alphabet.end()){
                if (find(foute_symbolen.begin(),foute_symbolen.end(),transition_symbol) == foute_symbolen.end()){
                    foute_symbolen.push_back(transition_symbol);
                }
                foutsymbool = true;
            }
        }
    }
    if (foutsymbool == true){
        cout << "symbool(en): ";
        for (int i = 0; i < foute_symbolen.size()-1; ++i){
            cout << foute_symbolen[i]<< ",";
        }
        cout << foute_symbolen.back();
        cout << " staat/staan niet in het alphabet!" << endl;

        return false;
    }
    return true;
}

bool NFA::accepts(string s) {
    if (this->isgeldig(s) == false){
        return false;
    }
    vector<string> currentstates;
    currentstates.push_back(start_state);
    for (int i = 0; i < s.size(); ++i) {
        string transition_symbol;
        transition_symbol.push_back(s[i]);
        vector<string> nextstate;
        for (int j = 0; j < currentstates.size(); ++j) {
            vector<string> next = this->go_to(currentstates[j], transition_symbol);
            nextstate.insert( nextstate.end(), next.begin(), next.end());
        }
        sort(nextstate.begin(), nextstate.end());
        nextstate.erase(std::unique(nextstate.begin(), nextstate.end()),nextstate.end());
        currentstates = nextstate;
    }
    for(string states:final_states){
        for (int i = 0; i < currentstates.size(); ++i) {
            if (currentstates[i] == states){
                return true;
            }
        }
    }
    return false;
}

bool NFA::hasTransitionon(string state,string transitie){
    for (map<string,vector<vector<string>>>::iterator it=transitie_tabel.begin(); it!=transitie_tabel.end(); ++it){
        if(it->first == state){
            for (int i = 0; i < it->second.size(); ++i){
                if(find(it->second[i].begin(), it->second[i].end(), transitie) != it->second[i].end()){
                    return true;
                }
            }
        }
    }
    return false;
}

// Dit is een methode die ik zelf heb gemaakt om de NFA in tabelvorm weer te geven
void NFA::print_tabel() {
    cout << type << ":\t";
    for (int i = 0; i < alphabet.size(); ++i){
        cout << " " << alphabet[i] << "\t";
    }
    cout << endl;
    for (int i = 0; i < alphabet.size()+1; ++i){
        cout << "=======";
    }
    cout << endl;
    for (map<string,vector<vector<string>>>::iterator it=transitie_tabel.begin(); it!=transitie_tabel.end(); ++it){
        if(this->isStartState(it->first) ){
            cout << "->";
        }
        if (this->isFinalState(it->first)){
            cout << " *";
        }
        if (!this->isFinalState(it->first) &&!this->isStartState(it->first)){
            cout << "  ";
        }
        cout << it->first << "  |"<< "\t";
        for (int i = 0; i < alphabet.size(); ++i){
            if(this->hasTransitionon(it->first,alphabet[i])){
                cout << "{";
                for (int j = 0; j < it->second.size(); ++j){
                    if(it->second[j][1] == alphabet[i]){
                        if(j > 0 && it->second[j-1][1] == alphabet[i]){
                            cout << ",";
                        }
                        cout << it->second[j][0];
                    }
                }
                cout << "}";
                cout << "\t";
            }
            else{
                cout << " /";
            }
        }
        cout << endl;
    }
}

bool NFA::isStartState(string state){
    if(state == start_state){
        return true;
    }
    return false;
}

bool NFA::isFinalState(string state){
    for (int i = 0; i < state.size(); ++i){
        for(string final_state:final_states){
            string staat;
            staat = state[i];
            if (staat == final_state){
                return true;
            }
        }
    }
    return false;
}


void NFA::print(){
    json j2;
    j2["type"] = type;
    j2["alphabet"] = alphabet;
    for (int i = 0; i < states.size(); ++i) {
        j2["states"][i]["name"] = states[i];
        j2["states"][i]["starting"] = this->isStartState(states[i]);
        j2["states"][i]["accepting"] = this->isFinalState(states[i]);
    }
    for (int i = 0; i < transitions.size(); ++i) {
        j2["transitions"][i]["from"] = transitions[i][0];
        j2["transitions"][i]["to"] = transitions[i][1];
        j2["transitions"][i]["input"] = transitions[i][2];
    }
    cout << setw(4) << j2 << endl;
}

void sort_state(vector<string> &NFAstates){
    vector<string> sorted;
    sort(NFAstates.begin(), NFAstates.end());
    // We halen ook duplicats er uit bijvoorbeeld:
    // bij de staat {x,y} we van x naar z gaan en van y naar z dan zal dit {z,z} worden wat niet de bedoeling is
    NFAstates.erase( unique( NFAstates.begin(), NFAstates.end() ), NFAstates.end() );
}

string toDFAstate(vector<string> NFAstates){
    if(!NFAstates.empty()){
        // We gaan de vector omzetten naar een staat van de vorm {x,y,...}
        string DFAstaat = "{";
        // Deze zal tevens gesorteerd worden.
        sort_state(NFAstates);

        for (int i = 0; i < NFAstates.size()-1; ++i) {
            DFAstaat += NFAstates[i];
            DFAstaat += ",";
        }
        DFAstaat += NFAstates.back();
        DFAstaat += "}";
        return DFAstaat;
    }
    else{
        return "{death}";
    }
}

vector<string> NFA::DFAtransitions(string from, vector<string> &DFA_states, vector<string> &final_states, string input, bool &deathstate){
    // We maken een transitie aan bestaande uit [[from],[to],[input]]
    vector<string> transition;
    vector<string> DFAstaat;
    // We voegen from al toe
    transition.push_back(from);
    // We ittereren over de staat en bekijken de individuele NFA transitions bv: {1,3} ->{4} en ->{2} dus wordt dit {4,2}
    // De 4 en 2 worden aan een tijdelijke vector DFA staat toegevoegd en later met de toDFAstate naar een string omgezet
    // [4,2] -> {2,4}
    for(int j = 0; j < from.size(); ++j){
        string state_;
        state_ = from[j];
        if (state_ != "{" and state_ != "}" and state_ != ","){
            vector<string> volgende_staat = (this->go_to(state_,input));
            DFAstaat.insert(DFAstaat.end(), volgende_staat.begin(), volgende_staat.end());
        }
    }
    string to = toDFAstate(DFAstaat);
    // We voegen de staat die we zijn bekomen aan de transitie toe

    if (!DFAstaat.empty()){
        transition.push_back(to);
    }
    else{
        transition.push_back("{death}");
        deathstate = true;
    };
    // We gaan geen dubbele staten toevoegen aan de DFA_states
    if (find(DFA_states.begin(), DFA_states.end(),to) == DFA_states.end()){
        DFA_states.push_back(to);
    }
    // We gaan ook over de staat om te kijken of er een finale staat tussen zit
    if(isFinalState(to)){
        final_states.push_back(to);
    }
    // dan voegen we het input symbool toe en en hebben we een volledige stransitie
    transition.push_back(input);
    return transition;
}

DFA NFA::toDFA(){
    vector<vector<string>> DFA_transitions;
    vector<string> DFA_alphabet = alphabet;
    vector<string> DFA_states;
    vector<string> startstate;
    startstate.push_back(start_state);
    string DFA_start_state = toDFAstate(startstate);
    vector<string> DFA_final_states;

    // DFA states is een lijst met strings die de staten bijhoud.
    DFA_states.push_back(toDFAstate(startstate));
    bool verwerken = true;
    bool deathstate = false;
    int counter = 0;
    // We blijven de staten verwerken tot alle staten een transitie in de DFA hebben
    while (verwerken){
        for(int i = 0; i < alphabet.size(); ++i){
            // een DFA_transition bestaat uit [[from],[to],[input]]
            DFA_transitions.push_back(this->DFAtransitions(DFA_states[counter],DFA_states, DFA_final_states, alphabet[i], deathstate));
            }
        counter+=1;
        if (DFA_states.size() <= counter){
            verwerken = false;
        }
    }
    // Als er naar een deathstate verwezen wordt moeten we die op het einde nog toevoegen
    if (deathstate == true){
        DFA_states.push_back("{death}");
        for(int i = 0; i < alphabet.size(); ++i){
            vector<string> transition;
            transition.push_back("{death}");
            transition.push_back("{death}");
            transition.push_back(alphabet[i]);
            DFA_transitions.push_back(transition);
        }
    }

    DFA dfa("DFA",DFA_transitions,DFA_alphabet,DFA_states,DFA_start_state,DFA_final_states);
    return dfa;
}

const string &NFA::getColor() const {
    return Color;
}
