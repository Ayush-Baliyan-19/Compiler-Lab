#include <iostream>
#include <stack>

int main() {
    std::stack<int> myStack; // Creating a stack of integers

    // Pushing elements onto the stack
    myStack.push(5);
    myStack.push(10);
    myStack.push(15);

    // Displaying the elements in the stack
    std::cout << "Elements in the stack are: ";
    while (!myStack.empty()) {
        std::cout << myStack.top() << " "; // Accessing the top element
        myStack.pop(); // Removing the top element
    }
    std::cout << std::endl;

    return 0;
}