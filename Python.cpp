#include "Python.h"
#include "sstream"
#include <algorithm>

ColorScheme::ColorScheme(const char *filename) {
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

    txt_file.close();
    make_color_scheme();
}

void ColorScheme::make_color_scheme() {
    int line_nr = 1;
    while(line_nr != line_list.size()){
        string line_content = line_list[line_nr];
        vector<string> words = split_line(line_content, ' ');
        bool comment = false;
        string sstring;
        for(const string &word : words){
            if(matchColor(word, sstring) == Grey || comment){
                colored_words[line_nr].push_back(make_pair(word, "#808080"));
                comment = true;
            } else if(matchColor(word, sstring) == Green){
                colored_words[line_nr].push_back(make_pair(word, "#72bf45"));
            }
            else if(matchColor(word, sstring) == Indigo){
                colored_words[line_nr].push_back(make_pair(word, "#4a3c8c"));
            } else if(matchColor(word, sstring) == Orange){
                colored_words[line_nr].push_back(make_pair(word, "#e07822"));
            }
            else if(matchColor(word, sstring) == Yellow){
                colored_words[line_nr].push_back(make_pair(word, "#dedb31"));
            }
//            else if(matchColor(word, sstring) == Blue){
//                colored_words[line_nr].push_back(make_pair(word, "#91c1e6"));
//            }
            else{
                colored_words[line_nr].push_back(make_pair(word, "no_color"));
            }
        }
        line_nr++;
    }

}

vector<string> ColorScheme::split_line(string &s, char d) {
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

ColorEnum ColorScheme::matchColor(const string &s, string &sstring) {
    if(s[0] == '#'){
        return Grey;
//    } else if(){
//
    } else if(find(used_words[Indigo].begin(), used_words[Indigo].end(), s) != used_words[Indigo].end()){
        return Indigo;
    } else if(find(used_words[Orange].begin(), used_words[Orange].end(), s) != used_words[Orange].end()){
        return Orange;
    } else if(find(used_words[Yellow].begin(), used_words[Yellow].end(), s) != used_words[Yellow].end()){
        return Yellow;
    }
//    else if(){
//        return Green
//    }
    return NoColor;
}
