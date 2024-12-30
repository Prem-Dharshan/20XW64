#include <iostream>
#include <unordered_map>
#include <regex>

using namespace std;

unordered_map<string, string> macros = {
    {"PI", "3.14159"},
    {"AREA", "(PI * (r) * (r))"}
};

string expandMacrosInLine(const string& line) {
    string expandedLine = line;
    for (const auto& [key, value] : macros) {
        regex macroRegex("\\b" + key + "\\b");
        expandedLine = regex_replace(expandedLine, macroRegex, value);
    }
    return expandedLine;
}

int main() {
    string code = "std::cout << \"Circle Area: \" << AREA(5) << std::endl;";

    // Expand macros in the code
    string expandedCode = expandMacrosInLine(code);

    // Now expandedCode should have AREA(5) replaced by (3.14159 * (5) * (5))
    cout << "Expanded code: " << expandedCode << endl;

    return 0;
}
