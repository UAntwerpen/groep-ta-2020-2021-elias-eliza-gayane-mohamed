#ifndef PYDE_WRAPPER_RE_H
#define PYDE_WRAPPER_RE_H

#include "../automata_elias/RE_elias.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "../../json.hpp"
#include "wrapper_ENFA.h"

using namespace std;
class RE {
private:
    RE_elias reElias;
public:

    RE(const string &regex, char epsilon);

    ENFA toENFA();

};


#endif //PYDE_WRAPPER_RE_H
