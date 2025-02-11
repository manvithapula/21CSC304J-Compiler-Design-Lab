#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// Function to split input string by '|'
vector<string> splitProductions(const string &prod) {
    vector<string> result;
    stringstream ss(prod);
    string token;
    while (getline(ss, token, '|')) {
        result.push_back(token);
    }
    return result;
}

// Function to remove left recursion
void eliminateLeftRecursion(string nonTerminal, vector<string> productions) {
    string newNonTerminal = nonTerminal + "'";
    vector<string> alpha, beta;

    for (const string &prod : productions) {
        if (prod[0] == nonTerminal[0]) {
            alpha.push_back(prod.substr(1)); // Store recursive part
        } else {
            beta.push_back(prod); // Store non-recursive part
        }
    }

    if (alpha.empty()) {
        cout << nonTerminal << " -> ";
        for (size_t i = 0; i < productions.size(); i++) {
            cout << productions[i] << (i == productions.size() - 1 ? "" : " | ");
        }
        cout << endl;
        return;
    }

    // New rules after elimination
    cout << nonTerminal << " -> ";
    for (size_t i = 0; i < beta.size(); i++) {
        cout << beta[i] << newNonTerminal << (i == beta.size() - 1 ? "" : " | ");
    }
    cout << endl;

    cout << newNonTerminal << " -> ";
    for (size_t i = 0; i < alpha.size(); i++) {
        cout << alpha[i] << newNonTerminal << " | ";
    }
    cout << "ε" << endl;
}

// Function to apply left factoring
void leftFactor(string nonTerminal, vector<string> productions) {
    map<string, vector<string>> factored;
    
    for (const string &prod : productions) {
        string prefix = prod.substr(0, 1); // Take the first character as prefix
        factored[prefix].push_back(prod.substr(1)); // Store remaining part
    }

    if (factored.size() == productions.size()) {
        cout << nonTerminal << " -> ";
        for (size_t i = 0; i < productions.size(); i++) {
            cout << productions[i] << (i == productions.size() - 1 ? "" : " | ");
        }
        cout << endl;
        return;
    }

    string newNonTerminal = nonTerminal + "'";
    cout << nonTerminal << " -> ";
    for (auto &p : factored) {
        cout << p.first << newNonTerminal << " | ";
    }
    cout << endl;

    cout << newNonTerminal << " -> ";
    for (auto &p : factored) {
        for (string rem : p.second) {
            cout << (rem.empty() ? "ε" : rem) << " | ";
        }
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of grammar rules: ";
    cin >> n;
    cin.ignore();

    map<string, vector<string>> grammar;
    for (int i = 0; i < n; i++) {
        string input;
        cout << "Enter production (e.g., S -> S a | b): ";
        getline(cin, input);

        size_t pos = input.find("->");
        if (pos == string::npos) {
            cout << "Invalid format! Use '->' to separate LHS and RHS.\n";
            return 1;
        }

        string nonTerminal = input.substr(0, pos - 1);
        string rhs = input.substr(pos + 3);
        grammar[nonTerminal] = splitProductions(rhs);
    }

    cout << "\nEliminating Left Recursion:\n";
    for (auto &rule : grammar) {
        eliminateLeftRecursion(rule.first, rule.second);
    }

    cout << "\nApplying Left Factoring:\n";
    for (auto &rule : grammar) {
        leftFactor(rule.first, rule.second);
    }

    return 0;
}
