#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <regex>

using namespace std;
namespace fs = std::filesystem;

// Function to check if a string matches the pattern (a|b)*abb
bool isValid(const string& str) {
    // Regular expression to match any combination of a's and b's followed by "abb"
    regex pattern("(a|b)*abb");
    return regex_match(str, pattern);
}

// Function to read test case files from the ./tests directory and process them
void processTestCases(const string& testDir, const string& outputDir) {
    // Create output directory if it doesn't exist
    fs::create_directory(outputDir);
    
    // Iterate through the test files in the directory
    for (const auto& entry : fs::directory_iterator(testDir)) {
        if (entry.is_regular_file()) {
            string testFile = entry.path().string();
            
            // Open test file and read the string
            ifstream inputFile(testFile);
            if (!inputFile.is_open()) {
                cerr << "Error: Could not open file " << testFile << endl;
                continue;
            }
            
            string testCase;
            getline(inputFile, testCase);
            inputFile.close();
            
            // Check if the test case matches the pattern
            bool result = isValid(testCase);
            
            // Output file path in ./output directory
            string outputFile = outputDir + "/" + entry.path().filename().string();
            ofstream outFile(outputFile);
            if (outFile.is_open()) {
                outFile << (result ? "Valid" : "Invalid") << endl;
                outFile.close();
            } else {
                cerr << "Error: Could not write to file " << outputFile << endl;
            }
        }
    }
}

int main() {
    string testDir = "./tests";
    string outputDir = "./output";

    // Process test cases
    processTestCases(testDir, outputDir);

    cout << "Processing completed. Check the output folder for results." << endl;
    return 0;
}
