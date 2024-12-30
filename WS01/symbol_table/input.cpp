#include <iostream>
using namespace std;

int main() {
    int x;         // Global variable
    float y = 3.14; // Global variable
    char c = 'A';   // Global variable
    bool flag;      // Global variable
    long count;     // Global variable
    
    if (x > 0) {
        int temp = 5;  // Local variable inside if
    }

    for (int i = 0; i < 10; i++) {
        float z = 2.5f; // Local variable inside loop
    }

    return 0;
}
