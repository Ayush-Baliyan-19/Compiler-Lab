#include <iostream>
#include <cctype>

void identifyTokens(const std::string& input) {
    std::string alphanumeric = "";
    std::string operations = "";

    for (char c : input) {
        if (std::isalnum(c)) { // Check if character is alphanumeric
            alphanumeric += c;
        } else {
            operations += c;
        }
    }

    std::cout << "Alphanumeric characters: " << alphanumeric << std::endl;
    std::cout << "Operations: " << operations << std::endl;
}

int main() {
    std::string inputString = "abc123+def-456*xyz";
    std::cout << "Input String: " << inputString << std::endl;

    std::cout << "Identified Tokens:\n";
    identifyTokens(inputString);

    return 0;
}