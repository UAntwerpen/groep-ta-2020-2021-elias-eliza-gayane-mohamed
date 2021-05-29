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
    for(int i = 1; i <= line_list.size(); i++) {
        parsed_file[i] = split_line(line_list[i]);
    }
    /// tot hier

    txt_file.close();
}

vector<string> Parser::split_line(string &s) {
    vector<string> words;
    string word;
    bool dubble_quotes = false;
    bool hashtag = false;
    for(int i = 0; i < s.size(); i++){
        if((!isalnum(s[i]) || (!isalnum(word[0]) && !word.empty())) && !dubble_quotes && !hashtag){
            words.emplace_back(word);
            word.clear();
        }
        if(s[i] == '#' && !dubble_quotes){
            hashtag = true;
        }
        if(s[i] == '\"' && dubble_quotes){
            dubble_quotes = false;
        }
        else if(s[i] == '\"' && !dubble_quotes){
            dubble_quotes = true;
        }
        if(s[i] != '\r'){
            word += s[i];
        }
        if(i == s.size() - 1) words.emplace_back(word);
    }
    for(int i = 0; i < words.size(); i++){
        if(words[i].empty()) words.erase(words.begin() + i);
    }
    return words;
}

map<int, vector<string>> &Parser::getParsedFile(){
    return parsed_file;
}

