#include "RE_elias.h"



RE_elias::RE_elias(const string &regex, char epsilon) : regex(regex), epsilon(epsilon) {
    aantal_states = 1;
    make_transitions();
    //vector<int> staten;
    //print(regextree, staten);
}

void RE_elias::print(node* current, vector<int> staten){
    staten.push_back(current->nummer);
    if(current->left){
        cout << "from: " << current->nummer << "\nto: " << current->left->nummer << "\nsymbool: " << current->transition_symbol << endl;
        if(find(staten.begin(), staten.end(), current->left->nummer) == staten.end()){
            print(current->left, staten);
        }
    }
    if(current->right){
        cout << "from: " << current->nummer << "\nto: " << current->right->nummer << "\nsymbool: " << current->transition_symbol << endl;
        if(find(staten.begin(), staten.end(), current->right->nummer) == staten.end()){
            print(current->right, staten);
        }
    }
}


node* ga_naar_starthaakje(node* current){
    //cout << "ga_naar_starthaakje: " << current->transition_symbol << endl;
    bool found = false;
    while (!found){
        if(current->starthaakje){
            found = true;
            //cout << "return_starthaakje: " << current->transition_symbol << endl;
            return current;
        }
        else{
            current = current->prev;
            //cout << "tussenstap: " << current->transition_symbol << endl;
        }
    }
}

node* ga_naar_eindthaakje(node* current){
    //cout << "ga_naar_starthaakje: " << current->transition_symbol << endl;
    bool found = false;
    while (!found){
        if(current->eindhaakje){
            found = true;
            //cout << "return_starthaakje: " << current->transition_symbol << endl;
            return current;
        }
        else{
            current = current->left;
            //cout << "tussenstap: " << current->transition_symbol << endl;
        }
    }
}

node* ga_naar_startstaat(node* current){
    //cout << "ga_naar_startstaat: " << current->transition_symbol << endl;
    bool found = false;
    while (!found){
        if(current->start){
            found = true;
            //cout << "return_starthaakje: " << current->transition_symbol << endl;
            return current;
        }
        else{
            current = current->prev;
            //cout << "tussenstap: " << current->transition_symbol << endl;
        }
    }
}

void get_alle_states_zonder_transities(node* current, vector<node*> &staten_zonder_trasities, vector<int> controlevector){
    controlevector.push_back(current->nummer);
    if(current->left == nullptr && current->right == nullptr){
        if(find(staten_zonder_trasities.begin(), staten_zonder_trasities.end(), current) == staten_zonder_trasities.end()) {
            staten_zonder_trasities.push_back(current);
        }
    }
    if(current->left){
        if(find(controlevector.begin(), controlevector.end(), current->left->nummer) == controlevector.end()){
            get_alle_states_zonder_transities(current->left, staten_zonder_trasities, controlevector);
        }
    }
    if(current->right){
        if(find(controlevector.begin(), controlevector.end(), current->right->nummer) == controlevector.end()){
            get_alle_states_zonder_transities(current->right, staten_zonder_trasities, controlevector);
        }
    }
}

void maak_lus_toe(node* current, char epsilon, int &aantal_states){
    //cout << "aanroep: " << current->transition_symbol << endl;
    aantal_states += 1;
    node* finalnode = new node(false,true, false, false,epsilon, nullptr,nullptr, nullptr, aantal_states);

    bool all_conected = false;
    bool lastnode = false;
    vector<node*> tussennode;
    int counter = 0;
    while (!all_conected){
        while (current->left != nullptr) {
            current = current->left;
        }
        if(lastnode){
            if(!tussennode.empty()){
                for (int i = 0; i < tussennode.size(); ++i) {
                    node* newnode_ = tussennode[tussennode.size()-1-i];
                    current->left = newnode_;
                    newnode_->prev = current;
                    if(current->left){
                        current = current->left;
                    }
                }
            }
        }
        else{
            for (int i = 0; i < counter; ++i) {
                if(i == 0){
                    aantal_states += 1;
                    node* newnode = new node(false,false, false, false,epsilon, nullptr,nullptr, nullptr, aantal_states);
                    current->left = newnode;

                    newnode->prev = current;

                    tussennode.push_back(newnode);
                    current = current->left;
                }
                if (i > 0){
                    node* newnode_ = tussennode[i-1];
                    current->left = newnode_;
                    newnode_->prev = current;
                    current = current->left;
                }
            }
        }
        current->left = finalnode;
        finalnode->prev = current;
        current = ga_naar_starthaakje(current);
        for (int i = 0; i < counter; ++i) {
            current = current->right;
        }
        //cout << current->right->transition_symbol << endl;
        if(lastnode == true){
            all_conected = true;
        }
        if(current->right == nullptr){
            break;
        }
        if(current->right != nullptr){
            if(current->right->right == nullptr){
                //cout << current->right->transition_symbol << " null" << endl;
                lastnode = true;
            }
            current = current->right;
            counter += 1;
        }
    }
}

void RE_elias::make_transitions(){
    bool ishaakjeingelezen = false;
    bool beginhaakje = false;
    int haakjescounter = 0;
    node* current = new node(false,false, true, false,epsilon, nullptr,nullptr, nullptr, aantal_states);
    regextree = current;
    current->start = true;
    current->transition_symbol = epsilon;
    for(int i = 0; i < regex.size(); ++i){
        //cout << regex[i] << endl;
        if(regex[i] == '('){
            beginhaakje = true;
            ishaakjeingelezen = true;
            haakjescounter += 1;
        }
        else if(regex[i] == ')'){
            if (ishaakjeingelezen){
                current = ga_naar_starthaakje(current);
            }
            maak_lus_toe(current, epsilon, aantal_states);
            ishaakjeingelezen = false;
            current = ga_naar_eindthaakje(current);
            aantal_states += 1;
            node* newlastnode = new node(false,false, false, false, epsilon, nullptr,nullptr, nullptr,aantal_states);
            //cout << current->nummer << endl;
            current->right = newlastnode;
            newlastnode->prev = current;
            current = current->right;

        }
        else if(regex[i] == '*'){
            aantal_states += 1;
            node* newfirstnode = new node(false,false, false, false, epsilon, nullptr,nullptr, nullptr,aantal_states);
            current = ga_naar_starthaakje(current);
            node* go_to = current;
            current = ga_naar_eindthaakje(current);
            //cout << current->nummer << "," << current->left << "," <<  current->right << endl;
            node* end = current->right;
            //cout << end->nummer << endl;
            current->left = go_to;
            current = ga_naar_starthaakje(current);
            if (current->start) {
                newfirstnode->start = true;
                regextree = newfirstnode;
                current->start = false;
            }
            if(current->prev){
                if(current->prev->left = current){
                    current->prev->left = newfirstnode;
                    newfirstnode->prev = current->prev;
                }
                else if(current->prev->right = current){
                    current->prev->right = newfirstnode;
                    newfirstnode->prev = current->prev->right;
                }
                else{
                   cout << "hier mag ik niet komen" << endl;
                }
                newfirstnode->left = current;
                current->prev = newfirstnode;
                newfirstnode->right = end;
                current = ga_naar_eindthaakje(current)->right;
            }
        }
        else if(regex[i] == '+'){
            if (ishaakjeingelezen){
                current = ga_naar_starthaakje(current);
                while (current->right != nullptr) {
                    //cout << current->transition_symbol << endl;
                    current = current->right;
                }

            }
            else{
                current = ga_naar_startstaat(current);
            }
            aantal_states += 1;
            node* newnode = new node(false,false, false, false,epsilon, nullptr,nullptr, nullptr,aantal_states);
            aantal_states += 1;
            node* newrightnode = new node(false,false, false, false,epsilon, nullptr,nullptr, nullptr,aantal_states);
            if (current->start){
                newnode->start = true;
                regextree = newnode;
                current->start = false;
                if (current->starthaakje){
                    newnode->starthaakje = true;
                    current->starthaakje = false;

                }
            }
            else{
                current->prev->right = newnode;
                newnode->prev = current->prev;
                if(current->prev->left == current){
                    current->prev->left = NULL;
                }
                if (current->starthaakje){

                    newnode->starthaakje = true;
                    current->starthaakje = false;

                }
            }
            newnode->left = current;
            newnode->right = newrightnode;

            newrightnode->prev = newnode;

            current->prev = newnode;
            current = newnode->right;
        }
        else{
            aantal_states += 1;
            node* newnode = new node(false,false, false, false, epsilon, nullptr,nullptr, nullptr,aantal_states);
            current->left = newnode;
            newnode->prev = current;
            newnode->transition_symbol = regex[i];
            if(beginhaakje){
                newnode->starthaakje = true;
                beginhaakje = false;
            }
            current = current->left;
        }
    }
    // alle eindjes verbinden
    vector<node*> staten_zonder_trasities;
    aantal_states += 1;
    node* final_state = new node(false,false, false, true, epsilon, nullptr,nullptr, nullptr, aantal_states);
    current = ga_naar_startstaat(current);
    vector<int> controlevector;
    get_alle_states_zonder_transities(current, staten_zonder_trasities, controlevector);
    for(int i = 0; i < staten_zonder_trasities.size(); ++i){
        staten_zonder_trasities[i]->left = final_state;
        final_state->prev = staten_zonder_trasities[i];
    }
}


node::node(bool starthaakje_, bool eindhaakje_, bool start, bool final,
           char transitionSymbol, node *left, node *right, node *prev, int nummer_) : starthaakje(starthaakje_),
                                                                         eindhaakje(eindhaakje_), start(start),
                                                                         final(final),
                                                                         transition_symbol(transitionSymbol),
                                                                         left(left), right(right), prev(prev) , nummer(nummer_){

}

bool has_elements(vector<vector<string>> transitions, vector<string> transition){
    for(int i = 0; i < transitions.size(); ++i){
        if(transitions[i][0] == transition[0] && transitions[i][1] == transition[1] && transitions[i][2] == transition[2]){
            return true;
        }
    }
    return false;
}

void get_transitions(node* current, vector<vector<string>> &transitions){
    if(current->left){
        vector<string> transition;
        transition.push_back(to_string(current->nummer));
        transition.push_back(to_string(current->left->nummer));
        string symbol;
        symbol.push_back(current->transition_symbol);
        transition.push_back(symbol);
        if(!has_elements(transitions,transition)){
            //cout << "from: " << current->nummer << "\nto: " << current->left->nummer << "\nsymbool: " << current->transition_symbol << endl;
            transitions.push_back(transition);
            get_transitions(current->left, transitions);
        }
    }
    if(current->right){
        vector<string> transition;
        transition.push_back(to_string(current->nummer));
        transition.push_back(to_string(current->right->nummer));
        string symbol;
        symbol.push_back(current->transition_symbol);
        transition.push_back(symbol);
        if(!has_elements(transitions,transition)){
            //cout << "from: " << current->nummer << "\nto: " << current->right->nummer << "\nsymbool: " << current->transition_symbol << endl;
            transitions.push_back(transition);
            get_transitions(current->right, transitions);
        }
    }
}

vector<string> get_alphabet(string regex, char epsilon){
    vector<string> alphabet;
    for(int i = 0; i < regex.size(); ++i){
        if(regex[i] != '(' && regex[i] != ')' && regex[i] != '+' && regex[i] != '*' && regex[i] != epsilon){
            string symbol;
            symbol.push_back(regex[i]);
            if(find(alphabet.begin(),alphabet.end(),symbol) == alphabet.end()){
                alphabet.push_back(symbol);
            }
        }
    }
    return alphabet;
}

vector<string> get_states(int aantal_states){
    vector<string> states;
    for(int i = 1; i < aantal_states+1; ++i){
        states.push_back(to_string(i));
    }
    return states;
}

void get_final_states(node* current, vector<string> &finale_states, vector<int> states){
    if(current->final){
        string nummer = to_string(current->nummer);
        if(find(finale_states.begin(), finale_states.end(), nummer) == finale_states.end()){
            finale_states.push_back(nummer);
        }
    }
    states.push_back(current->nummer);
    if(current->left){
        if(find(states.begin(), states.end(), current->left->nummer) == states.end()){
            get_final_states(current->left, finale_states, states);
        }
    }
    if(current->right){
        if(find(states.begin(), states.end(), current->right->nummer) == states.end()){
            get_final_states(current->right, finale_states,  states);
        }
    }
}

ENFA_elias RE_elias::toENFA(){
    vector<vector<string>> transitions;
    get_transitions(regextree,transitions);
    string epsilon_;
    epsilon_.push_back(epsilon);
    vector<string> alphabet = get_alphabet(regex, epsilon);
    vector<string> states = get_states(aantal_states);
    string startstaat = to_string(regextree->nummer);
    vector<string> finalestates;
    vector<int> test;
    get_final_states(regextree,finalestates,test);
    return ENFA_elias("ENFA_elias", epsilon_, alphabet, states, startstaat, finalestates, transitions);
}

const string &RE_elias::getRegex() const {
    return regex;
}

char RE_elias::getEpsilon() const {
    return epsilon;
}

RE_elias::RE_elias() {}
