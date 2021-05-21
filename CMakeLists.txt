cmake_minimum_required(VERSION 3.16)
project(PYDE)

set(CMAKE_CXX_STANDARD 14)

add_executable(PYDE
        engine.cpp
        HTML.cpp
        HTML.h
        Parser.cpp
        Parser.h
        Safe.cpp
        Safe.h
        automata/automata_eliza/DFA_eliza.cpp
        automata/automata_eliza/DFA_eliza.h
        automata/automata_elias/DFA_elias.cpp
        automata/automata_elias/DFA_elias.h
        automata/automata_elias/NFA_elias.cpp
        automata/automata_elias/NFA_elias.h
        automata/automata_elias/ENFA_elias.h
        automata/automata_elias/ENFA_elias.cpp
        automata/automata_elias/RE_elias.h
        automata/automata_elias/RE_elias.cpp
        automata/wrappers/wrapper_DFA.cpp
        automata/wrappers/wrapper_DFA.h
        automata/wrappers/wrapper_NFA.cpp
        automata/wrappers/wrapper_NFA.h
        automata/wrappers/wrapper_ENFA.cpp
        automata/wrappers/wrapper_ENFA.h
        automata/wrappers/wrapper_RE.cpp
        automata/wrappers/wrapper_RE.h
        json.hpp)