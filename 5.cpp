#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
#include <cctype>

// Function to check if the character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to get precedence of an operator
int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to convert infix expression to postfix
std::string infixToPostfix(const std::string& infix) {
    std::stack<char> operatorStack;
    std::string postfix;

    // Map to handle parentheses for precedence
    std::unordered_map<char, int> precedence = {
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}
    };

    for (char c : infix) {
        if (std::isalnum(c)) { // If it's an operand, append to postfix string
            postfix += c;
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '(')
                operatorStack.pop();
        } else if (isOperator(c)) {
            while (!operatorStack.empty() && precedence[c] <= precedence[operatorStack.top()]) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

int main() {
    std::string infixExpression = "a+b*c-(d/e+f*g*h)";

    std::cout << "Infix Expression: " << infixExpression << std::endl;
    std::string postfixExpression = infixToPostfix(infixExpression);
    std::cout << "Postfix Expression: " << postfixExpression << std::endl;

    return 0;
}