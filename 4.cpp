#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <algorithm>

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

// Function to reverse a string
std::string reverseString(const std::string& str) {
    std::string reversed = str;
    std::reverse(reversed.begin(), reversed.end());
    return reversed;
}

// Function to convert infix expression to prefix
std::string infixToPrefix(const std::string& infix) {
    std::stack<char> operatorStack;
    std::string prefix;
    std::string reversedInfix = reverseString(infix);

    for (char c : reversedInfix) {
        if (std::isalnum(c)) { // If it's an operand, append to prefix string
            prefix += c;
        } else if (c == ')') {
            operatorStack.push(c);
        } else if (c == '(') {
            while (!operatorStack.empty() && operatorStack.top() != ')') {
                prefix += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == ')')
                operatorStack.pop();
        } else if (isOperator(c)) {
            while (!operatorStack.empty() && getPrecedence(c) < getPrecedence(operatorStack.top())) {
                prefix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
    }

    while (!operatorStack.empty()) {
        prefix += operatorStack.top();
        operatorStack.pop();
    }

    return reverseString(prefix);
}

int main() {
    std::string infixExpression = "(a+b*c)-(d/e+f*g*h)";

    std::cout << "Infix Expression: " << infixExpression << std::endl;
    std::string prefixExpression = infixToPrefix(infixExpression);
    std::cout << "Prefix Expression: " << prefixExpression << std::endl;

    return 0;
}