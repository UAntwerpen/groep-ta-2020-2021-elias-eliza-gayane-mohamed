#include "HTML.h"


HTML::HTML(const map<int, vector<pair<string, string>>> &text, const char *filename, const vector<string> &alleFiles)
        : text(text), filename(filename), alle_files(alleFiles) {
    make_HTML_file(text, filename, alleFiles);
}


void HTML::make_HTML_file(const map<int, vector<pair<string, string>>> &text, string filename, const vector<string> &alleFiles){
    std::ofstream html_file;
    size_t lastindex = filename.find_last_of(".");
    string filename_ = filename.substr(0, lastindex);
    string file = "output/" + filename_ + ".html";
    html_file.open(file);
    if (html_file.is_open()) {
        html_file << "<!DOCTYPE html>\n<html>\n<head>\n<link href=\"file.css\" rel=\"stylesheet\" type=\"text/css\">\n<title>PYDE</title>\n</head>\n<body style=\"background-color:#232323;\">\n";
        html_file << "<header>\n\t<table border=\"1\" bordercolor=\"dimgrey\">";
        for(int i = 0; i < alleFiles.size(); i++){
            if(filename == alleFiles[i]){
                html_file << "\n\t\t<td style=\"border-color: #afa8a8\">";
            }
            else{
                html_file << "\n\t\t<td>";
            }
            string herf = "<a href=\"";
            string html = ".html\">";
            string py = ".py</a>";
            string argv_ = alleFiles[i];
            size_t lastindex = argv_.find_last_of(".");
            string naam = argv_.substr(0, lastindex);
            string herf_ = herf+naam+html+naam+py;
            html_file << "\n\t\t\t" + herf_;
            html_file << "\n\t\t</td>";
        }
        html_file << "\n\t</table>\n</header>\n";
        html_file << "<p style=\"color:white;line-height:1.5\">";
        for (auto it = text.begin(); it != text.end(); ++it){
            string begin = "<span style=\"color: #5f5e5e;\">" + to_string(it->first) + "</span>";
            html_file << begin;
            for(int i = 0; i < it->second.size(); i++){
                cout << "spatie" << endl;
                if (i > 0 && i < it->second.size()-1){
                    if(it->second[i-1].first != "("&& it->second[i].first != ")" && it->second[i].first != "(" && it->second[i].first != ":"){
                        html_file << " ";
                    }
                }
                else if (i == it->second.size()-1){
                    if(it->second[it->second.size()-1].first != "(" && it->second[it->second.size()-1].first != ")"  && it->second[it->second.size()-1].first != ":"){
                        html_file << " ";
                    }
                }
                else{
                    html_file << " ";
                }
                if(it->second[i].second != "no_color"){
                    string color_begin = "<span style=\"color: " + it->second[i].second + ";\">";
                    string word = it->second[i].first;
                    string color_end = "</span>";
                    html_file << color_begin + word + color_end;
                }
                else{
                    html_file << it->second[i].first;
                }
                cout << it->second[i].first << endl;
            }
            html_file << "\n<br>";
        }
        html_file << "</p>\n</body>\n</html>";
    }
    html_file.close();
}

