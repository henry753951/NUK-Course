
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#define DEBUG 1

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
        return match(rules["<assign>"], input);
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

    bool match(vector<vector<Token>> alts, string input) {
        if (DEBUG) {
            cout << "input:\n\t" << input << endl
                 << "Trying:\n\t";
            for (int i = 0; i < alts.size(); i++) {
                for (auto token : alts[i]) {
                    cout << token.value << " ";
                }
                if (i != alts.size() - 1)
                    cout << " | ";
            }
            cout << endl;
        }

        vector<pair<string, string>> tokens;
        bool valid = false;
        sort(alts.begin(), alts.end(), [](const vector<Token>& a, const vector<Token>& b) {
            int count_a = 0, count_b = 0;
            for (const Token& token : a)
                if (token.type == TokenType::NonTerminal) count_a++;
            for (const Token& token : b)
                if (token.type == TokenType::NonTerminal) count_b++;
            return count_a > count_b;
        });

        for (const vector<Token>& alt : alts) {
            tokens.clear();
            string remaining = input;
            valid = true;
            for (int i = 0; i < alt.size(); i++) {
                if (alt[i].type == TokenType::STRING) {
                    size_t pos = remaining.find(alt[i].value);
                    if (pos == string::npos) {  // 此規則不符合 下一位
                        valid = false;
                        break;
                    }
                    string left = remaining.substr(0, pos);
                    if (!left.empty()) {
                        if (i - 1 >= 0 && alt[i - 1].type == TokenType::NonTerminal && match(rules[alt[i - 1].value], left)) {
                            tokens.push_back({alt[i - 1].value, left});
                            if (DEBUG) cout << "ncnc! " << endl;
                        } else {
                            valid = false;
                            break;
                        }
                    }
                    remaining = remaining.substr(pos + alt[i].value.size());
                }
            }
            if (valid) {
                if (!remaining.empty()) {
                    if (alt.back().type == TokenType::NonTerminal && match(rules[alt.back().value], remaining)) {
                        tokens.push_back({alt.back().value, remaining});
                    } else {
                        valid = false;
                        if (DEBUG) cout << "nice try ~ Undoing! " << endl;
                    }
                }
                break;
            }
        }

        if (!valid) return false;

        return true;
    }
};
