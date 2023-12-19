#include <iostream>
#include <map>
#include <set>
#include <vector>

// Define a structure for grammar production rules
struct Production {
    char nonTerminal;
    std::string expression;
};

// Function to calculate First set of symbols in a grammar
std::map<char, std::set<char>> calculateFirstSet(const std::vector<Production>& grammar) {
    std::map<char, std::set<char>> firstSet;

    // Initializing firstSet for non-terminals
    for (const auto& production : grammar) {
        firstSet[production.nonTerminal]; // Initialize non-terminal entries
    }

    bool changesMade = true;
    while (changesMade) {
        changesMade = false;
        for (const auto& production : grammar) {
            char nonTerminal = production.nonTerminal;
            const std::string& expression = production.expression;

            // If first character is terminal, add it to the First set
            if (isalpha(expression[0]) && islower(expression[0])) {
                if (firstSet[nonTerminal].insert(expression[0]).second) {
                    changesMade = true;
                }
            } else { // Handle non-terminal
                size_t i = 0;
                while (i < expression.size() && isupper(expression[i])) {
                    char symbol = expression[i];

                    // Copy firstSet of symbol to nonTerminal's First set
                    for (char terminal : firstSet[symbol]) {
                        if (firstSet[nonTerminal].insert(terminal).second) {
                            changesMade = true;
                        }
                    }

                    // Continue to next symbol if epsilon is in First(symbol)
                    if (firstSet[symbol].count('$') == 0) {
                        break;
                    }

                    ++i; // Move to next symbol
                }

                // If all symbols derive epsilon, add epsilon to First set of nonTerminal
                if (i == expression.size()) {
                    if (firstSet[nonTerminal].insert('$').second) {
                        changesMade = true;
                    }
                }
            }
        }
    }

    return firstSet;
}

int main() {
    // Example grammar productions
    std::vector<Production> grammar = {
        {'S', "aAB"},
        {'A', "b"},
        {'A', "$"},
        {'B', "c"},
        {'B', "$"}
    };

    // Calculate First sets for symbols in the grammar
    std::map<char, std::set<char>> firstSet = calculateFirstSet(grammar);

    // Displaying First sets
    std::cout << "First sets:\n";
    for (const auto& [symbol, first] : firstSet) {
        std::cout << "First(" << symbol << ") = { ";
        for (char terminal : first) {
            std::cout << terminal << " ";
        }
        std::cout << "}\n";
    }

    return 0;
}