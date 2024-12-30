#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <filesystem>

using namespace std;

// Function to read the content of a file
string readFileContent(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filepath << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to process includes
string processIncludes(const string& line) {
    regex includeRegex(R"(#include\s+[<"](.+)[>"])");
    smatch match;
    if (regex_search(line, match, includeRegex)) {
        string headerFile = match[1];

        // Adjust header file paths based on your library paths
        vector<string> includePaths = {
            "C:/msys64/ucrt64/include/",
            "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/13.2.0/include/",
            "C:/msys64/ucrt64/include/c++/13.2.0/"
        };

        for (const auto& path : includePaths) {
            string headerPath = path + headerFile;
            if (filesystem::exists(headerPath)) {
                return readFileContent(headerPath);
            }
        }
        return "// Error: Header file not found: " + headerFile + "\n";
    }
    return line;
}

// Function to dynamically expand macros in a line of code
string expandMacrosInLine(const string& line, const unordered_map<string, string>& macros) {
    string expandedLine = line;
    for (const auto& [key, value] : macros) {
        regex macroRegex("\\b" + key + "\\b"); // Match whole word only
        expandedLine = regex_replace(expandedLine, macroRegex, value);
    }
    return expandedLine;
}

// Main function to process a file
void processFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error: Could not open input or output file." << endl;
        return;
    }

    unordered_map<string, string> macros;
    string line;

    while (getline(inFile, line)) {
        // Process #include directives
        if (line.find("#include") == 0) {
            outFile << processIncludes(line);
        }
        // Process #define directives
        else if (line.find("#define") == 0) {
            regex defineRegex(R"(#define\s+(\w+)\s+(.+))");
            smatch match;
            if (regex_search(line, match, defineRegex)) {
                macros[match[1]] = match[2]; // Store macro definition
            }
        }
        // Substitute macros in other lines
        else {
            string expandedLine = expandMacrosInLine(line, macros);
            outFile << expandedLine << "\n";
        }
    }

    inFile.close();
    outFile.close();
    cout << "Processing completed. Output written to: " << outputFile << endl;
}

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    // Input and output file paths
    string inputFile = argv[1];
    string outputFile = argv[2];

    // Process the file
    processFile(inputFile, outputFile);

    return 0;
}
