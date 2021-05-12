#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cmath>
#include "automata/DFA_elias.h"

using namespace std;

int main(int argc, char const* argv[]) {
    for(int i = 1; i < argc; i++){
        ifstream txt_file;
        txt_file.open(argv[i]);
        string line;
        if (txt_file.is_open()) {
            while (getline(txt_file, line)) {
                cout << line << endl;
            }
        }
        rtfdjgjfdjgd
        txt_file.close();
    }
    return 0;
}
