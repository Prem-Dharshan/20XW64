#!/bin/bash

# Set the working directory for WS01
cd /d/Academics/20XW64/WS01

# 1. Compile and run the automaton cpp files
echo "Running automaton/automaton.cpp..."
g++ automaton/automaton.cpp -o automaton/automaton.exe
./automaton/automaton.exe

# 2. Compile and run preprocessor_dir_expansion cpp files
echo "Running preprocessor_dir_expansion/dir_expansion.cpp..."
g++ preprocessor_dir_expansion/dir_expansion.cpp -o preprocessor_dir_expansion/dir_expansion.exe
./preprocessor_dir_expansion/dir_expansion.exe

echo "Running preprocessor_dir_expansion/macro_expansion.cpp..."
g++ preprocessor_dir_expansion/macro_expansion.cpp -o preprocessor_dir_expansion/macro_expansion.exe
./preprocessor_dir_expansion/macro_expansion.exe

# 3. Compile and run the symbol table cpp files
echo "Running symbol_table/input.cpp..."
g++ symbol_table/input.cpp -o symbol_table/input.exe
./symbol_table/input.exe

echo "Running symbol_table/symbol_table.cpp..."
g++ symbol_table/symbol_table.cpp -o symbol_table/symbol_table.exe
./symbol_table/symbol_table.exe

# Optionally, you can include the compiled .exe file for symbol_table
./symbol_table/symbol_table.exe
