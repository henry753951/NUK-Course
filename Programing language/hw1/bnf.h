
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#define DEBUG 0

using namespace std;
enum class TokenType {
    NonTerminal,
    STRING,
};

struct Token {
    TokenType type;
    string value;
};

class BNF_statement {
   public:
    BNF_statement(string BNF) {
        cout << "BNF: \n"
             << BNF << endl;

        stringstream ss(BNF);
        string line;
        while (getline(ss, line)) {
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
            parseRule(line);
        }
    }

    unordered_map<string, vector<vector<Token>>> rules;
    bool is_valid(string input) {
        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
        this->input = input;
        size_t pos = 0;
        return TryEvetyAlt(rules["<assign>"], input);
    }

   private:
    string input;

    bool parseRule(const string& rule_str) {
        size_t pos = rule_str.find("->");
        if (pos == string::npos) return false;

        string lhs = rule_str.substr(0, pos);
        string rhs = rule_str.substr(pos + 2);

        stringstream ss(rhs);
        string token;
        while (getline(ss, token, '|')) {
            if (DEBUG) cout << "-----" << token << "-----" << endl;
            rules[lhs].push_back(parseToken(token));
            if (DEBUG) cout << endl;
        }

        return true;
    }
    vector<Token> parseToken(const string& token_str) {
        vector<Token> tokens;
        stringstream ss(token_str);
        string token;
        bool isTerminal = false;
        for (int i = 0; i < token_str.size(); i++) {
            if (token_str[i] == '<') {
                int j = i;
                while (token_str[j] != '>' && j < token_str.size()) {
                    isTerminal = true;
                    j++;
                }
                if (isTerminal) {
                    if (token.size() > 0)
                        tokens.push_back({TokenType::STRING, token});
                    token = token_str.substr(i, j - i + 1);
                    tokens.push_back({TokenType::NonTerminal, token});
                    token = "";
                    isTerminal = false;
                    i = ++j;
                }
            }
            if (!isTerminal) {
                token.append(token_str.substr(i, 1));
            }
        }
        if (token.size() > 0)
            tokens.push_back({TokenType::STRING, token});

        if (DEBUG)
            for (Token& token : tokens) {
                if (token.type == TokenType::NonTerminal)
                    cout << token.value << "\n";
                else
                    cout << token.value << "\n";
            }
        return tokens;
    }

    string getAltString(const vector<Token>& alt) {
        string result = "";
        for (const Token& token : alt) {
            if (token.type == TokenType::NonTerminal)
                result.append(token.value);
            else
                result.append(token.value);
        }
        return result;
    }

    bool TryEvetyAlt(vector<vector<Token>> alts, string input) {
        if (DEBUG) {
            cout << "Trying:" << endl;
            for (const vector<Token>& alt : alts)
                cout << getAltString(alt) << endl;
        }
        for (const vector<Token>& alt : alts) {
            if (alt.size() == 1 && alt[0].type == TokenType::STRING) {
                if (alt[0].value == input) {
                    if (DEBUG) cout << "input: " << input << endl;
                    if (DEBUG) cout << "Leave node Matched!" << endl;
                    return true;
                }
                continue;
            };
            vector<pair<Token, string>> temp;
            vector<vector<pair<Token, string>>> result = getAllPermutations(input, alt, 0, 0, temp);
            if (result.size() == 0) {
                if (DEBUG) cout << "input: " << input << endl;
                if (DEBUG) cout << getAltString(alt) << " not Matched!" << endl;
                continue;
            }
            if (DEBUG) cout << "input: " << input << endl;
            if (DEBUG) cout << getAltString(alt) << " Matched!" << endl;
            if (DEBUG) {
                cout << endl;
                cout << "result: " << endl;
                for (const vector<pair<Token, string>>& r : result) {
                    for (const pair<Token, string>& p : r) {
                        cout << p.first.value << " " << p.second << endl;
                    }
                    cout << endl;
                }
            }

            for (const vector<pair<Token, string>>& r : result) {
                bool valid = true;
                for (const pair<Token, string>& p : r) {
                    if(!TryEvetyAlt(rules[p.first.value], p.second)) valid = false;
                }
                if(valid) return true;
            }
        }
        return false;
    }

    vector<vector<pair<Token, string>>> getAllPermutations(const string& input, const vector<Token>& format, int i, int j, vector<pair<Token, string>>& current) {
        vector<vector<pair<Token, string>>> results;

        if (i == input.size() && j == format.size()) {
            results.push_back(current);
            return results;
        }
        if (i >= input.size() || j >= format.size()) {
            return results;
        }

        if (format[j].type == TokenType::NonTerminal) {
            for (int k = i; k < input.size(); k++) {
                vector<pair<Token, string>> new_current = current;
                new_current.push_back(make_pair(format[j], input.substr(i, k - i + 1)));
                auto new_results = getAllPermutations(input, format, k + 1, j + 1, new_current);
                results.insert(results.end(), new_results.begin(), new_results.end());
            }
        } else {
            int len = format[j].value.size();
            if (input.substr(i, len) == format[j].value) {
                auto new_results = getAllPermutations(input, format, i + len, j + 1, current);
                results.insert(results.end(), new_results.begin(), new_results.end());
            }
        }

        return results;
    }

    vector<size_t> find_all(const string& input, const string& query) {
        vector<size_t> positions;

        size_t pos = 0;
        while (true) {
            pos = input.find(query, pos);
            if (pos == string::npos) {
                break;
            }

            positions.push_back(pos);
            pos += query.size();
        }

        return positions;
    }
};
