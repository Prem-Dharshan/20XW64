#!/bin/bash

# Set the working directory for WS02
cd /d/Academics/20XW64/WS02

# 1. Compile and run DFA related C++ files
echo "Running dfa/dfa.cpp..."
g++ dfa/dfa.cpp -o output/dfa/dfa.exe
./output/dfa/dfa.exe

# 2. Compile and run NFA related C++ files
echo "Running nfa/nfa.cpp..."
g++ nfa/nfa.cpp -o output/nfa/nfa.exe
./output/nfa/nfa.exe

# Optional: Additional code if you have other tests to run within the output directories
echo "Running additional test cases for WS02..."

# You can also add logic for running specific test case scripts, depending on your structure.
