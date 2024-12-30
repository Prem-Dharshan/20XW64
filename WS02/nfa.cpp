#include <iostream>
#include <fstream>
#include <filesystem>
#include <set>

#define MAX_NFA_STATES 5
#define MAX_ALPHABET_SIZE 3 // For '0', '1', '2'

using namespace std;
namespace fs = std::filesystem;

class NFA {
    set<int> transitions[MAX_NFA_STATES][MAX_ALPHABET_SIZE];
    bool finalStates[MAX_NFA_STATES]{};
    int numStates;
    int initState;

public:
    NFA();
    bool simulate(const string& input);
    void addTransition(int fromState, char symbol, int toState);
};

NFA::NFA() {
    numStates = 5; // States: S0, S1, S2, S3, D
    initState = 0; // S0

    // Define transitions
    addTransition(0, '1', 1); // S0 --1--> S1
    addTransition(1, '0', 2); // S1 --0--> S2
    addTransition(2, '1', 1); // S2 --1--> S1 (loop back)
    addTransition(2, '0', 2); // S2 --0--> S2 (loop)
    addTransition(2, '2', 3); // S2 --2--> S3 (final state)

    finalStates[3] = true; // Only S3 is a final state
}

void NFA::addTransition(const int fromState, const char symbol, const int toState) {
    if (symbol == '0') transitions[fromState][0].insert(toState);
    else if (symbol == '1') transitions[fromState][1].insert(toState);
    else if (symbol == '2') transitions[fromState][2].insert(toState);
}

bool NFA::simulate(const string& input) {
    set<int> currentStates;
    currentStates.insert(initState); // Start with initial state

    for (const char c : input) {
        set<int> nextStates;
        for (const int state : currentStates) {
            if (c == '0') {
                nextStates.insert(transitions[state][0].begin(), transitions[state][0].end());
            } else if (c == '1') {
                nextStates.insert(transitions[state][1].begin(), transitions[state][1].end());
            } else if (c == '2') {
                nextStates.insert(transitions[state][2].begin(), transitions[state][2].end());
            }
        }
        currentStates = nextStates; // Move to next states
    }

    // Check if any of the current states are accepting states
    for (const int state : currentStates) {
        if (finalStates[state]) {
            return true; // Accepted
        }
    }

    return false; // Rejected
}

void processTestCases(const string& inputDir, const string& outputDir) {
    NFA nfa;

    fs::create_directories(outputDir); // Ensure output directory exists

    for (const auto& entry : fs::directory_iterator(inputDir)) {
        if (entry.path().extension() == ".txt") {
            ifstream inputFile(entry.path());
            if (!inputFile) {
                cerr << "Error opening file: " << entry.path() << endl;
                continue;
            }

            string line;
            if (getline(inputFile, line)) { // Read only one line per file
                bool result = nfa.simulate(line);
                
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
    const string inputDir = "./tests/nfa/";
    const string outputDir = "./output/nfa/";

    processTestCases(inputDir, outputDir);
    
    cout << "Processing complete. Check the output in " << outputDir << endl;

    return 0;
}
