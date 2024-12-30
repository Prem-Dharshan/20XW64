#include <iostream>
#include <fstream>
#include <filesystem>

#define MAX_DFA_STATES 5
#define MAX_ALPHABET_SIZE 3 // For '0', '1', '2'

using namespace std;
namespace fs = std::filesystem;

class DFA {
    int transitions[MAX_DFA_STATES][MAX_ALPHABET_SIZE]{};
    bool finalStates[MAX_DFA_STATES]{};
    int numStates;
    int initState;
    int deadState;

public:
    DFA();
    [[nodiscard]] bool simulate(const string& input) const;
};

DFA::DFA() {
    numStates = 5; // States: S0, S1, S2, S3, D
    initState = 0; // S0
    deadState = 4; // D

    // Initialize transitions to dead state by default
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < MAX_ALPHABET_SIZE; j++) {
            transitions[i][j] = deadState;
        }
    }

    // Define transitions
    transitions[0][1] = 1; // S0 --1--> S1
    transitions[1][0] = 2; // S1 --0--> S2
    transitions[2][1] = 1; // S2 --1--> S1 (loop back)
    transitions[2][0] = 2; // S2 --0--> S2 (loop)
    transitions[2][2] = 3; // S2 --2--> S3 (final state)
    
    finalStates[3] = true; // Only S3 is a final state
}

bool DFA::simulate(const string& input) const {
    int currentState = initState;
    
    for (const char c : input) {
        int symbol;
        if (c == '0') symbol = 0;
        else if (c == '1') symbol = 1;
        else if (c == '2') symbol = 2;
        else return false; // Invalid symbol

        currentState = transitions[currentState][symbol];
    }
    
    return finalStates[currentState]; // Check if the current state is accepting
}

void processTestCases(const string& inputDir, const string& outputDir) {
    fs::create_directories(outputDir); // Ensure output directory exists

    for (const auto& entry : fs::directory_iterator(inputDir)) {
        if (entry.path().extension() == ".txt") {
            ifstream inputFile(entry.path());
            if (!inputFile) {
                cerr << "Error opening file: " << entry.path() << endl;
                continue;
            }

            if (string line; getline(inputFile, line)) {
                DFA dfa;
                // Read only one line per file
                bool result = dfa.simulate(line);
                
                // Create an output file name based on the input file name
                string outputFileName = outputDir + "/" + entry.path().filename().string();
                ofstream outputFile(outputFileName);
                
                // Write both the test case and the result to the output file
                outputFile << "Test Case: " << line << endl;
                outputFile << "Result: " << (result ? "Accepted" : "Rejected") << endl;
                outputFile.close();
            }

            inputFile.close();
        }
    }
}

int main() {
    const string inputDir = "./tests/dfa/";
    const string outputDir = "./output/dfa/";

    processTestCases(inputDir, outputDir);
    
    cout << "Processing complete. Check the output in " << outputDir << endl;

    return 0;
}
