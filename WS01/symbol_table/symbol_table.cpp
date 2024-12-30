#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <vector>
#include <iomanip>

using namespace std;

// Structure to hold variable information (name, type, scope)
struct SymbolInfo {
    string type;
    string scope;
};

// Function to parse the code and build the symbol table
void buildSymbolTable(const string& code, unordered_map<string, SymbolInfo>& symbolTable) {
    // Regular expressions to match variable declarations
    regex varDeclRegex(R"((int|float|char|double|bool|long)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*(=.*)?;)");
    regex varDeclWithArrayRegex(R"((int|float|char|double|bool|long)\s+([a-zA-Z_][a-zA0-9_]*)(\[[^\]]*\])\s*;)");
    smatch match;
    
    // Sample scope for this example (can be improved with more advanced parsing)
    string currentScope = "global"; // Default scope

    // Parse the code and fill the symbol table
    stringstream ss(code);
    string line;
    while (getline(ss, line)) {
        // Check for variable declarations
        if (regex_search(line, match, varDeclRegex) || regex_search(line, match, varDeclWithArrayRegex)) {
            string type = match[1];     // Variable type
            string name = match[2];     // Variable name

            // Store the symbol with type and scope
            symbolTable[name] = SymbolInfo{type, currentScope};
        }
    }
}

// Function to display the symbol table in a tabular format with proper padding
void displaySymbolTable(const unordered_map<string, SymbolInfo>& symbolTable) {
    cout << "\nSymbol Table:\n";
    cout << "-----------------------------------------------\n";
    cout << "| Variable Name     | Type   | Scope     |\n";
    cout << "-----------------------------------------------\n";

    for (const auto& entry : symbolTable) {
        cout << "| "
             << left << setw(18) << entry.first  // Variable Name (padded to 18 characters)
             << "| "
             << left << setw(7)  << entry.second.type   // Type (padded to 7 characters)
             << "| "
             << left << setw(9)  << entry.second.scope  // Scope (padded to 9 characters)
             << "|\n";
    }

    cout << "-----------------------------------------------\n";
}

int main() {
    string fileName = "input.cpp";  // C++ code input file
    
    // Open the C++ code file
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return 1;
    }

    // Read the entire file content
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string code = buffer.str();
    inputFile.close();

    unordered_map<string, SymbolInfo> symbolTable;

    // Build the symbol table
    buildSymbolTable(code, symbolTable);

    // Display the symbol table
    displaySymbolTable(symbolTable);

    return 0;
}
