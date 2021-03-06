#include "DFA_elias.h"

DFA_elias::DFA_elias(const string &inputfile) : inputfile(inputfile) {

    readfile(inputfile);
}

void DFA_elias::readfile(string){
    ifstream input(inputfile);
    json j;
    input >> j;

    /// We gaan eerst alle componenten van de DFA_elias bepalen de quintuple: {Q,E,§,q0,F}
    type = j["type"];

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

void DFA_elias::maak_transitie_tabel(vector<vector<string>> transitions){
    for (int i = 0; i < states.size(); ++i) {
        vector<vector<string>> overgangen;
        for (int j = 0; j < transitions.size(); ++j){
            if(states[i] == transitions[j][0]){
                vector<string> item;
                item.push_back(transitions[j][1]);
                item.push_back(transitions[j][2]);
                overgangen.push_back(item);
            }
        }
        transitie_tabel[states[i]] = overgangen;
    }
}

string DFA_elias::go_to(vector<vector<string>> transitions , string current_state, string s){
    for (int i = 0; i < transitions.size(); ++i){
        //cout << "from: " << transitions[i][0] << " to: " << transitions[i][1] << " input: " << transitions[i][2] << endl;
        if (current_state == transitions[i][0] && transitions[i][2] == s){
            return transitions[i][1];
        }
    }
    return "";
}

string DFA_elias::goes_to(string current_state, string s){
    for (int i = 0; i < transitie_tabel[current_state].size(); ++i){
        //cout << "from: " << transitions[i][0] << " to: " << transitions[i][1] << " input: " << transitions[i][2] << endl;
        if (current_state == transitie_tabel[current_state][i][0] && transitie_tabel[current_state][i][2] == s){
            return transitie_tabel[current_state][i][1];
        }
    }
    return "";
}

bool DFA_elias::isgeldig(string s){
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
    /*
    if (foutsymbool == true){
        cout << "symbool(en): ";
        for (int i = 0; i < foute_symbolen.size()-1; ++i){
            cout << foute_symbolen[i]<< ",";
        }
        cout << foute_symbolen.back();
        cout << " staat/staan niet in het alphabet!" << endl;

        return false;
    }
     */
    return true;
}

bool DFA_elias::accepts(string s) {
    if (this->isgeldig(s) == false){
        return false;
    }
    string nextstate = start_state;
    for (int i = 0; i < s.size(); ++i) {
        string transition_symbol;
        transition_symbol = s[i];
        nextstate = this->go_to(transitions, nextstate, transition_symbol);
    }
    for(string states:final_states){
        if (nextstate == states){
            return true;
        }
    }
    return false;
}

void DFA_elias::print_tabel() {
    cout << type << ":\t";
    for (int i = 0; i < alphabet.size(); ++i){
        cout << " " << alphabet[i] << "\t";
    }
    cout << endl;
    cout << "===========";
    for (int i = 0; i < alphabet.size()+1; ++i){
        cout << "=====";
    }
    cout << endl;
    for (map<string,vector<vector<string>>>::iterator it=transitie_tabel.begin(); it!=transitie_tabel.end(); ++it){
        if(this->isStartState(it->first) ){
            cout << "->";
        }
        if (this->isFinalState(final_states,it->first)){
            cout << " *";
        }
        if (!this->isFinalState(final_states, it->first) &&!this->isStartState(it->first)){
            cout << "  ";
        }
        cout << it->first << "\t|\t";
        for (int i = 0; i < alphabet.size(); ++i){
            for (int j = 0; j < alphabet.size(); ++j){
                if(it->second[j][1] == alphabet[i]){
                    cout << it->second[j][0] << "\t";
                }
            }
        }
        cout << endl;
    }
}

bool DFA_elias::isStartState(string state){
    if(state == start_state){
        return true;
    }
    return false;
}

bool DFA_elias::isFinalState(vector<string> final_states_, string state){
    for(string final_state:final_states_){
        if (state == final_state){
            return true;
        }
    }
    return false;
}


void DFA_elias::print(){
    json j2;
    j2["type"] = type;
    j2["alphabet"] = alphabet;
    for (int i = 0; i < states.size(); ++i) {
        j2["states"][i]["name"] = states[i];
        j2["states"][i]["starting"] = this->isStartState(states[i]);
        j2["states"][i]["accepting"] = this->isFinalState(final_states, states[i]);
    }
    for (int i = 0; i < transitions.size(); ++i) {
        j2["transitions"][i]["from"] = transitions[i][0];
        j2["transitions"][i]["to"] = transitions[i][1];
        j2["transitions"][i]["input"] = transitions[i][2];
    }
    cout << setw(4) << j2 << endl;
}

// functie om te kijken of een bepaalde vector in een matrix zit
bool isintabel(vector<vector<string>> tabel,vector<string> subset){
    string logo1 = subset[0];
    string logo2 = subset[1];
    if(logo1 == logo2){
        return true;
    }
    for (int i = 0; i < tabel.size(); ++i) {
        string logo3 = tabel[i][0];
        string logo4 = tabel[i][1];
        if ((logo1 == logo3 && logo2 == logo4) || (logo1 == logo4 && logo2 == logo3)){
            return true;
        }
    }
    return false;
}

// funtie die een tabel initialiseerd voor het table filling algoritme
map<pair<string,string>,string> maketabel(vector<string> states){
    map<pair<string,string>,string> tabel;
    sort(states.begin(), states.end());
    states.erase(std::unique(states.begin(), states.end()), states.end());
    for (int i = 0; i < states.size()-1; ++i){
        for (int j = i+1; j < states.size(); ++j){
            tabel[make_pair(states[i],states[j])] = "-";
        }
    }
    return tabel;
}

DFA_elias::DFA_elias(const string &type, const vector<vector<string>> &transitions, const vector<string> &alphabet,
                     const vector<string> &states, const string &startState, const vector<string> &finalStates) : type(type),
         transitions(transitions),alphabet(alphabet),states(states),start_state(startState),final_states(finalStates) {
    maak_transitie_tabel(transitions);

}

// functie die nagaat of een bepaalde combinatie een kruisje heeft
bool heeft_kruisje(map<pair<string,string>,string> &tabel, pair<string,string> combinatie1, pair<string,string> combinatie2){
    if(tabel[combinatie1] == "X"){
        return true;
    }
    else if(tabel[combinatie2] == "X"){
        return true;
    }
    return false;
}

// functie die het bepaalde teken van een combinatie terug geeft
string vind_teken(vector<string> combinatie, vector<vector<string>> tabel){
    string logo1 = combinatie[0];
    string logo2 = combinatie[1];
    for (int i = 0; i < tabel.size(); ++i) {
        string logo3 = tabel[i][0];
        string logo4 = tabel[i][1];
        if ((logo1 == logo3 && logo2 == logo4) || (logo1 == logo4 && logo2 == logo3)) {
            return tabel[i][2];
        }
    }
}

// functie die 2 tabellen met elkaar vergelijkt
bool compare(map<pair<string,string>,string> tabel, map<pair<string,string>,string> vorige_tabel){
    // we gaan de 2 tabellen vergeijken
    bool gelijk = true;
    for (std::map<pair<string,string>,string>::iterator it=tabel.begin(); it!=tabel.end(); ++it){

        if(it->second != vorige_tabel[it->first]){
            gelijk = false;
        }
    }
    return gelijk;
}

// functie die equivalente staten combineert en terug geeft
vector<vector<string>> equivalent(vector<vector<string>> tabel){
    vector<vector<string>> equivalent;
    for (int i = 0; i < tabel.size(); ++i){
        if (tabel[i][2] == "-"){
            vector<string> staten;
            staten.push_back(tabel[i][0]);
            staten.push_back(tabel[i][1]);
            equivalent.push_back(staten);
        }
    }
    vector<vector<string>> equivalent_;
    for (int i = 0; i < equivalent.size(); ++i){
        vector<string> staten;
        staten.push_back(equivalent[i][0]);
        staten.push_back(equivalent[i][1]);
        for (int j = 0; j < equivalent.size(); ++j){
            if(find(staten.begin(),staten.end(),equivalent[j][0]) != staten.end() || find(staten.begin(),staten.end(),equivalent[j][1]) != staten.end()){
                staten.push_back(equivalent[j][0]);
                staten.push_back(equivalent[j][1]);
                sort(staten.begin(),staten.end());
                staten.erase(std::unique(staten.begin(), staten.end()),staten.end());
            }
        }
        equivalent_.push_back(staten);
    }
    equivalent_.erase(std::unique(equivalent_.begin(), equivalent_.end()),equivalent_.end());
    if(equivalent_.size() == 0){
        vector<string> staten;
        equivalent_.push_back(staten);
    }
    return equivalent_;
}

// functie die van een bepaalde staten een DFA_elias string maakt
string to_dfa_staat(vector<string> eqiuvalent_states){
    if(!eqiuvalent_states.empty()){
        // We gaan de vector omzetten naar een staat van de vorm {x,y,...}
        string DFAstaat = "{";
        // Deze zal tevens gesorteerd worden.

        for (int i = 0; i < eqiuvalent_states.size()-1; ++i) {
            DFAstaat += eqiuvalent_states[i];
            DFAstaat += ", ";
        }
        DFAstaat += eqiuvalent_states.back();
        DFAstaat += "}";
        return DFAstaat;
    }
}

// methode die het table filling algoritme uitvoert
vector<vector<string>> DFA_elias::table_filling_algoritme(vector<vector<string>> transitions, vector<string> final_states, vector<string> states, map<pair<string,string>,string> &minimized){
    // een tabel is een matrix en ziet er als volgt uit [[x,y,teken],[z,y,teken],...]

    minimized = maketabel(states);

    // eerst gaan we alle ongelijke paren er uit halen
    // dit zijn de combinaties tussen de staten waarbij een staat finaal is en de andere niet
    for (std::map<pair<string,string>,string>::iterator it=minimized.begin(); it!=minimized.end(); ++it){
        string staat1 = it->first.first;
        string staat2 = it->first.second;
        if((isFinalState(final_states,staat1) && !isFinalState(final_states,staat2))){
            it->second = "X";
        }
        else if(!isFinalState(final_states,staat1) && isFinalState(final_states,staat2)){
            it->second = "X";
        }
    }

    // Daarna gaan we kijken naar waar de combinatie van staten gaan en als deze combinatie van staten een kruisje heeft
    // dan gaan we bij die combinatie ook een kruisje zetten.
    map<pair<string,string>,string>  vorige_tabel = minimized;
    bool voorwaarde = true;
    while (voorwaarde) {
        for (std::map<pair<string, string>, string>::iterator it = minimized.begin(); it != minimized.end(); ++it) {
            string teken = it->second;
            // als er nog geen kruisje staat gaan we vergelijken;
            if (teken == "-") {
                for (int j = 0; j < alphabet.size(); ++j) {

                    string volgende_staat1 = goes_to(it->first.first, alphabet[j]);
                    string volgende_staat2 = goes_to(it->first.second, alphabet[j]);
                    if (heeft_kruisje(minimized, make_pair(volgende_staat1, volgende_staat2),make_pair(volgende_staat2, volgende_staat1))){
                        it->second = "X";
                        break;
                    }
                }
            }
        }
        // We blijven doorgaan in de while loop tot dat de vorige tabel en de huidige tabel gelijk zijn
        // Dit zal betekenen dat alle mogelijke kruisjes gezet zijn
        if (compare(minimized, vorige_tabel)) {
            voorwaarde = false;
        }
        vorige_tabel = minimized;
    }
    vector<vector<string>> returnvector;
    for (std::map<pair<string, string>, string>::iterator it = minimized.begin(); it != minimized.end(); ++it) {
        vector<string> tussenstap;
        tussenstap.push_back(it->first.first);
        tussenstap.push_back(it->first.second);
        tussenstap.push_back(it->second);
        returnvector.push_back(tussenstap);
    }
    return returnvector;
}

// functie die de tabel print
void DFA_elias::printTable(){
    int counter = 1;
    while (counter < states.size()){
        for (int i = 1; i < states.size(); i++) {
            cout << states[i] << "\t";
            for (int j = 0; j < counter-1; ++j) {
                cout << minimized_tabel[make_pair(states[i],states[j])] << "\t";
            }
            cout << minimized_tabel[make_pair(states[i],states[counter-1])] << endl;
            counter += 1;
        }
    }
    cout << "\t";
    for (int i = 0; i < states.size()-2; i++) {
        cout << states[i] << "\t";
    }
    cout << states[states.size()-2]<< endl;
}

// functie die de tabel print voor de equils operator
void printTable_equils(vector<string> states, vector<vector<string>> minimized_tabel){
    int counter = 1;
    while (counter < states.size()){
        for (int i = 1; i < states.size(); i++) {
            cout << states[i] << "\t";
            for (int j = 0; j < counter-1; ++j) {
                vector<string> combinatie;
                combinatie.push_back(states[i]);
                combinatie.push_back(states[j]);
                cout << vind_teken(combinatie, minimized_tabel) << "\t";
            }
            vector<string> combinatie;
            combinatie.push_back(states[i]);
            combinatie.push_back(states[counter-1]);
            cout << vind_teken(combinatie, minimized_tabel) << endl;
            counter += 1;
        }
    }
    cout << "\t";
    for (int i = 0; i < states.size()-2; i++) {
        cout << states[i] << "\t";
    }
    cout << states[states.size()-2]<< endl;
}

vector<string> parse_state_(string state){
    vector<string> returnwaarde;
    std::string s = state.substr(1,state.size()-2);
    std::string delimiter = ",";

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        returnwaarde.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    returnwaarde.push_back(s);
    return returnwaarde;
}

// functie die de overeenkomstige staat van de neiuwe geminimaliseerde DFA_elias terug geeft
string get_overeenlomstige_nieuwe_staat(vector<string> newDFAstates, string staat){
    for (int i = 0; i < newDFAstates.size(); i++){
        vector<string> appartre_states = parse_state_(newDFAstates[i]);
        for (int j = 0; j < appartre_states.size(); j++) {
            if (staat == appartre_states[j]){
                return newDFAstates[i];
            }
        }
    }
}

// methode die de nieuwe DFA_elias transities bepaald
vector<string> DFA_elias::DFAtransitions(vector<string> newDFAstates, string from, vector<string> &DFA_states, string input){
    // We maken een transitie aan bestaande uit [[from],[to],[input]]
    vector<string> transition;
    vector<string> DFAstaat;
    transition.push_back(from);
    vector<string> from_ = parse_state_(from);
    string to;
    for(int i = 0; i < from_.size(); ++i){
        string state_ = from_[i];
        // we gaan kijken naar waar de staten in de dfa gaan en dan gaan we de overeenkomstige nieuwe staat bepalen die we gevonden hebben door het table filling algoritme
        to = get_overeenlomstige_nieuwe_staat(newDFAstates, this->go_to(transitions,state_,input));
        transition.push_back(to);
        break;
    }
    // We gaan geen dubbele staten toevoegen aan de DFA_states
    if (find(DFA_states.begin(), DFA_states.end(),to) == DFA_states.end()){
        DFA_states.push_back(to);
    }
    transition.push_back(input);
    return transition;
}

// methode die een DFA_elias minimaliseerd door middle van het table filling algoritme
DFA_elias DFA_elias::minimize(){

    // tabel is een matrix en ziet er als volgt uit [[x,y,teken],[z,y,teken],...]
    vector<vector<string>> tabel = this->table_filling_algoritme(transitions,final_states,states,minimized_tabel);
    // eqiuvalent_states is een matrix en ziet er als volgt uit [[equivalente_staat1,equivalente_staat2,.. ],[equivalente_staat3,equivalente_staat4,.. ],...]
    vector<vector<string>> eqiuvalent_states = equivalent(tabel);


    // newDFAstates is een vector en ziet er als volgt uit [{staat1},{staat2}...]
    vector<string> newDFAstates;
    for (int i = 0; i < states.size(); i++) {
        bool found = false;
        for (int j = 0; j < eqiuvalent_states.size(); j++) {
            if(find(eqiuvalent_states[j].begin(),eqiuvalent_states[j].end(),states[i]) != eqiuvalent_states[j].end()){
                string staat = to_dfa_staat(eqiuvalent_states[j]);
                found = true;
                if(find(newDFAstates.begin(),newDFAstates.end(),staat) == newDFAstates.end()){
                    newDFAstates.push_back(staat);
                }
            }
        }
        if(!found){
            string staat = "{"+states[i]+"}";
            if(find(newDFAstates.begin(),newDFAstates.end(),staat) == newDFAstates.end()){
                newDFAstates.push_back(staat);
            }
        }
    }

    string DFAstartstate;
    for (int i = 0; i < newDFAstates.size(); i++){
        vector<string> states = parse_state_(newDFAstates[i]);
        for (int j = 0; j < states.size(); j++){
            if(states[i] == start_state){
                DFAstartstate = "{"+states[i]+"}";
            }
        }
    }

    vector<string> DFA_final_states;
    for (int i = 0; i < newDFAstates.size(); i++){
        vector<string> geparsed = parse_state_(newDFAstates[i]);
        for (int j = 0; j < geparsed.size(); j++){
            if(isFinalState(final_states,geparsed[j])){
                string final_state = get_overeenlomstige_nieuwe_staat(newDFAstates, geparsed[j]);
                if(find(DFA_final_states.begin(),DFA_final_states.end(),final_state) == DFA_final_states.end()){
                    DFA_final_states.push_back(final_state);
                }
            }
        }
    }

    // newDFAtransitions is een matrix en ziet er als volgt uit [[from:{staat1},to:{staat2},input:symbool],[from:{staat1},to:{staat3},input:symbool],...]
    vector<vector<string>> newDFAtransitions;

    // DFA_elias states is een lijst met strings die de staten bijhoud.
    vector<string> DFA_states;
    DFA_states.push_back(DFAstartstate);
    bool verwerken = true;
    int counter = 0;
    // We blijven de staten verwerken tot alle staten een transitie in de DFA_elias hebben
    while (verwerken){
        for(int i = 0; i < alphabet.size(); ++i){
            // een DFA_transition bestaat uit [[from],[to],[input]]
            newDFAtransitions.push_back(DFAtransitions(newDFAstates,DFA_states[counter],DFA_states, alphabet[i]));
        }
        counter+=1;
        if (DFA_states.size() <= counter){
            verwerken = false;
        }
    }
    DFA_elias dfa("DFA_elias", newDFAtransitions, alphabet, DFA_states, DFAstartstate, DFA_final_states);
    return dfa;
}

// methode die nagaat of 2 DFA_elias's gelijk zijn
bool DFA_elias::operator == (const DFA_elias &other){
    vector<string> allestaten;
    vector<string> allfinalstates;
    vector<vector<string>> alletransities;
    for (int i = 0; i < this->states.size(); ++i){
        allestaten.push_back(this->states[i]);
    }
    for (int i = 0; i < this->transitions.size(); ++i){
        alletransities.push_back(this->transitions[i]);
    }
    for (int i = 0; i < this->final_states.size(); ++i){
        allfinalstates.push_back(this->final_states[i]);
    }
    for (int i = 0; i < other.states.size(); ++i){
        allestaten.push_back(other.states[i]);
    }
    for (int i = 0; i < other.transitions.size(); ++i){
        alletransities.push_back(other.transitions[i]);
    }
    for (int i = 0; i < other.final_states.size(); ++i){
        allfinalstates.push_back(other.final_states[i]);
    }
    map<pair<string,string>,string> tablefilling = maketabel(allestaten);
    vector<vector<string>> tabel = this->table_filling_algoritme(alletransities,allfinalstates,allestaten,tablefilling);
    printTable_equils(allestaten,tabel);

    // Om te kijken of 2 DFA_elias's gelijk zijn moeten we kijken naar de startstaten
    // Als deze equivalent zijn volgens het table fillig algoritme dan zijn de DFA_elias's equivalent
    vector<vector<string>> equivalent;
    for (int i = 0; i < tabel.size(); ++i){
        if (tabel[i][2] == "-"){
            vector<string> staten;
            staten.push_back(tabel[i][0]);
            staten.push_back(tabel[i][1]);
            equivalent.push_back(staten);
        }
    }
    for (int i = 0; i < equivalent.size(); ++i){
        string otherstartstate = other.start_state;
        if(equivalent[i][0] == this->start_state && equivalent[i][1] == otherstartstate || equivalent[i][1] == this->start_state && equivalent[i][0] == otherstartstate){
            return true;
        }
    }
    return false;
}

DFA_elias::DFA_elias() {}
