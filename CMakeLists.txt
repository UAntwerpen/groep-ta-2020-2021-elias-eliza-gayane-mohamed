cmake_minimum_required(VERSION 3.16)
project(PYDE)

set(CMAKE_CXX_STANDARD 14)

add_executable(PYDE
        engine.cpp
        HTML.cpp
        HTML.h
        Parser.cpp
        Parser.h
        automata/DFA_elias.cpp
        automata/DFA_elias.h
        automata/NFA_elias.cpp
        automata/NFA_elias.h
        automata/ENFA_elias.h
        automata/ENFA_elias.cpp
        automata/RE_elias.h
        automata/RE_elias.cpp
        json.hpp)