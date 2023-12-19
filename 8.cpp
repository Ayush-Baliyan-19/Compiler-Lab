#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

// Function to remove left recursion from a grammar
std::map<char, std::vector<std::string>> removeLeftRecursion(std::map<char, std::vector<std::string>>& grammar) {
    std::map<char, std::vector<std::string>> newGrammar;

    for (auto& rule : grammar) {
        char nonTerminal = rule.first;
        std::vector<std::string>& productions = rule.second;

        std::vector<std::string> alpha, beta;
        for (const std::string& prod : productions) {
            if (prod[0] == nonTerminal) {
                beta.push_back(prod.substr(1) + nonTerminal + "'");
            } else {
                alpha.push_back(prod + nonTerminal + "'");
            }
        }

        if (!beta.empty()) {
            newGrammar[nonTerminal] = beta;
            newGrammar[nonTerminal].push_back("ε");
        }

        if (!alpha.empty()) {
            newGrammar[nonTerminal + "'"] = alpha;
            newGrammar[nonTerminal + "'"].push_back("ε");
        }
    }

    for (auto& rule : newGrammar) {
        char nonTerminal = rule.first;
        std::vector<std::string>& productions = rule.second;

        std::vector<std::string> updatedProductions;
        for (std::string& prod : productions) {
            if (prod[0] == nonTerminal) {
                std::string suffix = prod.substr(1);
                for (const std::string& newProd : newGrammar[nonTerminal]) {
                    updatedProductions.push_back(newProd + suffix);
                }
            } else {
                updatedProductions.push_back(prod);
            }
        }
        productions = updatedProductions;
    }

    return newGrammar;
}

int main() {
    // Example grammar with left recursion
    std::map<char, std::vector<std::string>> grammar = {
        {'E', {"E+T", "T"}},
        {'T', {"T*F", "F"}},
        {'F', {"(E)", "id"}}
    };

    std::cout << "Grammar before left recursion removal:" << std::endl;
    for (auto& rule : grammar) {
        std::cout << rule.first << " -> ";
        for (const std::string& prod : rule.second) {
            std::cout << prod << " | ";
        }
        std::cout << std::endl;
    }

    std::map<char, std::vector<std::string>> newGrammar = removeLeftRecursion(grammar);

    std::cout << "\nGrammar after left recursion removal:" << std::endl;
    for (auto& rule : newGrammar) {
        std::cout << rule.first << " -> ";
        for (const std::string& prod : rule.second) {
            std::cout << prod << " | ";
        }
        std::cout << std::endl;
    }

    return 0;
}