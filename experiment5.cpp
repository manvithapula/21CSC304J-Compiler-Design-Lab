#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> productions;
map<char, set<char>> firstSets, followSets;
set<char> nonTerminals, terminals;
char startSymbol;

// Function to remove left recursion
void removeLeftRecursion() {
    map<char, vector<string>> newProductions;
    
    for (char A : nonTerminals) {
        vector<string> alpha, beta;
        
        for (const string &prod : productions[A]) {
            if (prod[0] == A) // Left recursion exists
                alpha.push_back(prod.substr(1));
            else
                beta.push_back(prod);
        }

        if (!alpha.empty()) {
            char newNonTerminal = A + '\'';
            nonTerminals.insert(newNonTerminal);

            for (const string &b : beta)
                newProductions[A].push_back(b + newNonTerminal);

            for (const string &a : alpha)
                newProductions[newNonTerminal].push_back(a + newNonTerminal);
            
            newProductions[newNonTerminal].push_back("$"); // Represents epsilon
        } else {
            newProductions[A] = productions[A];
        }
    }
    productions = newProductions;
}

// Function to perform left factoring
void leftFactorGrammar() {
    map<char, vector<string>> newProductions;
    
    for (char A : nonTerminals) {
        map<string, vector<string>> prefixGroups;
        
        for (const string &prod : productions[A]) {
            prefixGroups[prod.substr(0, 1)].push_back(prod.substr(1));
        }

        for (auto &[prefix, group] : prefixGroups) {
            if (group.size() > 1) { // Need left factoring
                char newNonTerminal = A + '\'';
                nonTerminals.insert(newNonTerminal);
                newProductions[A].push_back(prefix + newNonTerminal);

                for (const string &suffix : group)
                    newProductions[newNonTerminal].push_back(suffix.empty() ? "$" : suffix);
            } else {
                newProductions[A].push_back(prefix + group[0]);
            }
        }
    }
    productions = newProductions;
}

// Function to compute FIRST set
set<char> computeFirst(char symbol) {
    if (firstSets.count(symbol)) return firstSets[symbol];

    set<char> first;
    if (islower(symbol) || symbol == '$') {
        first.insert(symbol);
        return first;
    }

    for (const string &prod : productions[symbol]) {
        for (char ch : prod) {
            set<char> subFirst = computeFirst(ch);
            first.insert(subFirst.begin(), subFirst.end());
            if (subFirst.find('$') == subFirst.end()) break;
        }
    }
    return firstSets[symbol] = first;
}

// Function to compute FOLLOW set
void computeFollow(char symbol) {
    if (followSets.count(symbol)) return;
    
    set<char> &follow = followSets[symbol];
    if (symbol == startSymbol) follow.insert('#'); // End of input marker

    for (const auto &[lhs, rhsList] : productions) {
        for (const string &rhs : rhsList) {
            for (size_t i = 0; i < rhs.length(); i++) {
                if (rhs[i] == symbol) {
                    bool isLast = (i == rhs.length() - 1);
                    if (!isLast) {
                        set<char> nextFirst = computeFirst(rhs[i + 1]);
                        follow.insert(nextFirst.begin(), nextFirst.end());
                        follow.erase('$');
                        if (nextFirst.find('$') != nextFirst.end() || isLast) {
                            computeFollow(lhs);
                            follow.insert(followSets[lhs].begin(), followSets[lhs].end());
                        }
                    } else {
                        computeFollow(lhs);
                        follow.insert(followSets[lhs].begin(), followSets[lhs].end());
                    }
                }
            }
        }
    }
}

// Function to create Predictive Parsing Table
map<pair<char, char>, string> createParsingTable() {
    map<pair<char, char>, string> parsingTable;
    
    for (const auto &[lhs, rhsList] : productions) {
        for (const string &rhs : rhsList) {
            set<char> first = computeFirst(rhs[0]);

            for (char terminal : first) {
                if (terminal != '$') parsingTable[{lhs, terminal}] = rhs;
            }

            if (first.find('$') != first.end()) {
                for (char terminal : followSets[lhs]) {
                    parsingTable[{lhs, terminal}] = "$";
                }
            }
        }
    }
    return parsingTable;
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cout << "Enter productions (e.g., S=abS | aSb):\n";

    for (int i = 0; i < n; i++) {
        string rule;
        cin >> rule;
        char lhs = rule[0];
        string rhs = rule.substr(2);
        nonTerminals.insert(lhs);
        
        stringstream ss(rhs);
        string token;
        while (getline(ss, token, '|')) {
            productions[lhs].push_back(token);
            for (char ch : token) {
                if (!isupper(ch) && ch != '$') terminals.insert(ch);
            }
        }
    }

    startSymbol = *nonTerminals.begin();
    removeLeftRecursion();
    leftFactorGrammar();

    for (char nt : nonTerminals) computeFirst(nt);
    for (char nt : nonTerminals) computeFollow(nt);

    map<pair<char, char>, string> parsingTable = createParsingTable();

    cout << "\nParsing Table:\n";
    for (const auto &[key, value] : parsingTable) {
        cout << "M[" << key.first << ", " << key.second << "] = " << value << "\n";
    }

    return 0;
}
