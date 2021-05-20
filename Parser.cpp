#include "Parser.h"

Parser::Parser(const char *filename) {
    ifstream txt_file;
    txt_file.open(filename);
    string line;

    if (txt_file.is_open()) {
        int line_nr = 1;
        while (getline(txt_file, line)) {
            line_list[line_nr] = line;
            line_nr++;
        }
    }
    else {
        cerr << "Error opening file " << filename << "." << endl;
    }
    /// dit heb ik erbij gedaan
    for(int i = 0; i < line_list.size(); i++) {
        parsed_file[i] = split_line(line_list[i], ' ');
    }
    /// tot hier

    txt_file.close();
}

vector<string> Parser::split_line(string &s, char d) {
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '#' || s[i] == ' ' || s[i] == '\"') continue;
        if (!isalnum(s[i])) {
            s.insert(s.begin() + i, ' ');
            s.insert(s.begin() + i + 2, ' ');
            i++;
        }
    }
    istringstream iss(s);
    string word;
    vector<string> words;
    while(getline(iss, word, d)){
        words.push_back(word);
    }
    return words;
}

map<int, vector<string>> &Parser::getParsedFile(){
    return parsed_file;
}

