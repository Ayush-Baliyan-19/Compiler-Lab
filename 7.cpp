#include <iostream>
#include <vector>
#include <map>
#include <set>

void leftFactorGrammar(std::map<char, std::set<std::string>>& grammar) {
    std::map<char, std::vector<std::string>> newProductions;

    for (auto& prod : grammar) {
        char nonTerminal = prod.first;
        std::set<std::string>& rules = prod.second;

        std::map<std::string, std::set<char>> prefixMap;

        for (const std::string& rule : rules) {
            std::string prefix;
            for (char c : rule) {
                prefix += c;
                prefixMap[prefix].insert(c);
            }
        }

        for (auto& prefix : prefixMap) {
            if (prefix.second.size() > 1) {
                char newNonTerminal = 'Z'; // New non-terminal for left factoring
                while (grammar.find(newNonTerminal) != grammar.end()) {
                    newNonTerminal++;
                }

                std::string newRule = prefix.first.substr(0, prefix.first.size() - 1);
                newProductions[nonTerminal].push_back(newRule + newNonTerminal);

                for (const std::string& rule : rules) {
                    if (rule.find(prefix.first) == 0) {
                        std::string newSuffix = rule.substr(prefix.first.size());
                        if (newSuffix.empty()) {
                            newProductions[newNonTerminal].push_back("ε");
                        } else {
                            newProductions[newNonTerminal].push_back(newSuffix);
                        }
                    }
                }
            }
        }
    }

    for (auto& prod : newProductions) {
        grammar[prod.first].clear();
        for (const std::string& rule : prod.second) {
            grammar[prod.first].insert(rule);
        }
    }
}

int main() {
    // Example grammar before left factoring
    std::map<char, std::set<std::string>> grammar = {
        {'S', {"abX", "abY"}},
        {'X', {"c", "ε"}},
        {'Y', {"d", "ε"}}
    };

    std::cout << "Grammar before left factoring:" << std::endl;
    for (auto& prod : grammar) {
        std::cout << prod.first << " -> ";
        for (const std::string& rule : prod.second) {
            std::cout << rule << " | ";
        }
        std::cout << std::endl;
    }

    leftFactorGrammar(grammar);

    std::cout << "\nGrammar after left factoring:" << std::endl;
    for (auto& prod : grammar) {
        std::cout << prod.first << " -> ";
        for (const std::string& rule : prod.second) {
            std::cout << rule << " | ";
        }
        std::cout << std::endl;
    }

    return 0;
}