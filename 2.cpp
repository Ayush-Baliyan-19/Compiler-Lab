#include <iostream>
#include <cctype>

void identifyTokens(const std::string& input) {
    std::string token = "";
    for (char c : input) {
        if (std::isalpha(c)) { // Check if character is an alphabet
            token += c;
            if (!std::isalpha(input[(input.find(c) + 1) % input.size()])) {
                std::cout << "Token: " << token << std::endl;
                token = ""; // Reset token after printing
            }
        } else if (std::isdigit(c)) { // Check if character is a digit
            token += c;
            if (!std::isdigit(input[(input.find(c) + 1) % input.size()])) {
                std::cout << "Token: " << token << std::endl;
                token = ""; // Reset token after printing
            }
        } else {
            std::cout << "Non-alphanumeric character encountered: " << c << std::endl;
        }
    }
}

int main() {
    std::string inputString = "abc123def456xyz";
    std::cout << "Input String: " << inputString << std::endl;

    std::cout << "Identified Tokens:\n";
    identifyTokens(inputString);

    return 0;
}