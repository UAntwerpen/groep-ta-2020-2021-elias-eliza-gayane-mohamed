#include "wrapper_RE.h"

RE::RE(const string &regex, char epsilon){
    RE_elias re_(regex, epsilon);
    reElias = re_;
}

ENFA RE::toENFA(){
    ENFA_elias enfaElias = reElias.toENFA();
    ENFA return_enfa(enfaElias);
    return return_enfa;
}

void RE::printStats(){
    reElias.printStats();
}