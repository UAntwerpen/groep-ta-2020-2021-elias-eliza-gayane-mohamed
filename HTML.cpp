#include "HTML.h"


HTML::HTML(const map<int, vector<pair<string, string>>> &text, const char *filename, const vector<string> &alleFiles)
        : text(text), filename(filename), alle_files(alleFiles) {
    make_HTML_file(text, filename, alleFiles);
}


void HTML::make_HTML_file(const map<int, vector<pair<string, string>>> &text, string filename, const vector<string> &alleFiles){
    // de vele \t en \n zijn om de html file die gegenereerd wordt nog leesbaar te maken
    std::ofstream html_file;
    size_t lastindex = filename.find_last_of(".");
    string filename_ = filename.substr(0, lastindex);
    string file = "../../output/" + filename_ + ".html";
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
        html_file << "<table  style=\"color:white\">";
        for (auto it = text.begin(); it != text.end(); ++it){
            html_file << "\n\t<tr>\n\t\t<td>\n\t\t\t";
            string begin = "<span style=\"color: #5f5e5e;\">" + to_string(it->first) + "</span>";
            html_file << begin;
            html_file << "\n\t\t</td>\n\t\t<td>\n\t\t\t";
            for(int i = 0; i < it->second.size(); i++){
                if(it->second[i].second != "no_color"){
                    string color_begin = "<span style=\"color: " + it->second[i].second + ";\">";
                    string word = it->second[i].first;
                    string color_end = "</span>";
                    html_file << color_begin + word + color_end;
                }
                else{
                    if(it->second[i].first == " "){
                        html_file << "&nbsp;";
                    }
                    else{
                        html_file << it->second[i].first;
                    };

                }
            }
            html_file << "\n\t\t</td>\n\t</tr>";
        }
        html_file << "\n</table>\n</body>\n</html>";
    }
    html_file.close();
}

