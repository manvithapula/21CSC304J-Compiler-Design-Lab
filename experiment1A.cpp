#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// Function to return the precedence of an operator
int precedence(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to convert infix to postfix
string infixToPostfix(const string &infix) {
    stack<char> s;
    string postfix;

    for (char c : infix) {
        // If the character is an operand, add it to the output
        if (isdigit(c)) {
            postfix += c;
        }
        // If the character is '(', push it to the stack
        else if (c == '(') {
            s.push(c);
        }
        // If the character is ')', pop and append until '(' is found
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            if (!s.empty() && s.top() == '(') {
                s.pop();
            }
        }
        // If the character is an operator
        else if (isOperator(c)) {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }

    // Pop all the operators left in the stack
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

// Function to evaluate a postfix expression
int evaluatePostfix(const string &postfix) {
    stack<int> s;

    for (char c : postfix) {
        // If the character is an operand, push it to the stack
        if (isdigit(c)) {
            s.push(c - '0');
        }
        // If the character is an operator, pop two elements, evaluate, and push the result
        else if (isOperator(c)) {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();

            switch (c) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
                case '^': s.push(pow(a, b)); break;
            }
        }
    }

    return s.top();
}

int main() {
    string infix;
    cout << "Enter a valid infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Evaluation result: " << result << endl;

    return 0;
}

int precedence(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to convert infix to postfix
string infixToPostfix(const string &infix) {
    stack<char> s;
    string postfix;

    for (char c : infix) {
        // If the character is an operand, add it to the output
        if (isdigit(c)) {
            postfix += c;
        }
        // If the character is '(', push it to the stack
        else if (c == '(') {
            s.push(c);
        }
        // If the character is ')', pop and append until '(' is found
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            if (!s.empty() && s.top() == '(') {
                s.pop();
            }
        }
        // If the character is an operator
        else if (isOperator(c)) {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }

    // Pop all the operators left in the stack
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

// Function to evaluate a postfix expression
int evaluatePostfix(const string &postfix) {
    stack<int> s;

    for (char c : postfix) {
        // If the character is an operand, push it to the stack
        if (isdigit(c)) {
            s.push(c - '0');
        }
        // If the character is an operator, pop two elements, evaluate, and push the result
        else if (isOperator(c)) {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();

            switch (c) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
                case '^': s.push(pow(a, b)); break;
            }
        }
    }

    return s.top();
}

int main() {
    string infix;
    cout << "Enter a valid infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Evaluation result: " << result << endl;

    return 0;
}
