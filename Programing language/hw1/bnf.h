
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

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
    BNF_statement(string BNF);
    unordered_map<string, vector<vector<Token>>> rules;

    //
    // 判斷input是否符合規則
    //
    bool is_valid(string input);

   private:
    //
    //  把一行的規則解析成物件
    //  ex: "<assign> -> <id>=<expr> | <id>"
    //  -> rules["<assign>"] = {{"<id>", "=", "<expr>"}, {"<id>"}}
    //
    bool parseRule(const string& rule_str);

    //
    // 把一個token字串解析成物件
    // ex: "<id>=<expr>"
    // ->{
    //    {TokenType::NonTerminal,"<id>"},
    //    {TokenType::STR,"="},
    //    {TokenType::NonTerminal,"<expr>"}
    // }
    //
    vector<Token> parseToken(const string& token_str);

    //
    // 判斷input是否符合規則
    // 並使用遞迴的方式判斷
    //
    bool Match(vector<vector<Token>> alts, string input);

    //
    // 找出所有可能的組合
    // ex: input = "A+B+C"
    //     format = {"<expr>", "+", "<term>"}
    //     -> {"A","B+C"},{"A+B","C"}
    //
    vector<vector<pair<Token, string>>> getAllPermutations(const string& input, const vector<Token>& format, int i, int j, vector<pair<Token, string>>& current);

    //
    // 找出字串中所有query的位置
    //
    vector<size_t> find_all(const string& input, const string& query);
    string getAltString(const vector<Token>& alt);
};

BNF_statement::BNF_statement(string BNF) {
    cout << "BNF: \n"
         << BNF << endl;

    stringstream ss(BNF);
    string line;
    while (getline(ss, line)) {
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        parseRule(line);
    }
}

bool BNF_statement::is_valid(string input) {
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    size_t pos = 0;
    // 從<assign>開始判斷
    return Match(rules["<assign>"], input);
}

bool BNF_statement::parseRule(const string& rule_str) {
    size_t pos = rule_str.find("->");
    if (pos == string::npos) return false;

    string lhs = rule_str.substr(0, pos);
    string rhs = rule_str.substr(pos + 2);

    stringstream ss(rhs);
    string token;
    while (getline(ss, token, '|'))
        rules[lhs].push_back(parseToken(token));
    return true;
}

vector<Token> BNF_statement::parseToken(const string& token_str) {
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
    return tokens;
}

bool BNF_statement::Match(vector<vector<Token>> alts, string input) {
    // 每個規則都要試試看 (ex: <expr> - <term> | <id> 等於兩個規則)
    for (const vector<Token>& alt : alts) {
        if (alt.size() == 1 && alt[0].type == TokenType::STRING) {
            if (alt[0].value == input) return true;
            continue;
        };
        vector<pair<Token, string>> temp;
        vector<vector<pair<Token, string>>> result = getAllPermutations(input, alt, 0, 0, temp);
        // 如果找不到符合規則的組合就跳過該格式化 (ex: <expr> - <term>，但是input是A+B，就不會有組合，反之 A-B-B 會有組合 -> A,B-B or A-B,B)
        if (result.size() == 0) continue;
        // 每種組合都要試試看
        for (const vector<pair<Token, string>>& r : result) {
            bool valid = true;
            // 每種組合要全部都符合才算是符合
            for (const pair<Token, string>& p : r) {
                if (!Match(rules[p.first.value], p.second)) valid = false;
            }
            if (valid) return true;
            //
        }
        //
    }
    //
    return false;
}

vector<vector<pair<Token, string>>> BNF_statement::getAllPermutations(const string& input, const vector<Token>& format, int i, int j, vector<pair<Token, string>>& current) {
    vector<vector<pair<Token, string>>> results;

    if (i == input.size() && j == format.size()) {
        results.push_back(current);
        return results;
    }
    if (i >= input.size() || j >= format.size()) {
        return results;
    }
    // 如果是NonTerminal，就把所有可能的組合都找出來
    if (format[j].type == TokenType::NonTerminal) {
        for (int k = i; k < input.size(); k++) {
            vector<pair<Token, string>> new_current = current;
            new_current.push_back(make_pair(format[j], input.substr(i, k - i + 1)));
            auto new_results = getAllPermutations(input, format, k + 1, j + 1, new_current);
            results.insert(results.end(), new_results.begin(), new_results.end());
        }
    } else {
        // 如果是Terminal，就直接比對
        int len = format[j].value.size();
        if (input.substr(i, len) == format[j].value) {
            auto new_results = getAllPermutations(input, format, i + len, j + 1, current);
            results.insert(results.end(), new_results.begin(), new_results.end());
        }
    }
    return results;
}

string BNF_statement::getAltString(const vector<Token>& alt) {
    string result = "";
    for (const Token& token : alt) {
        if (token.type == TokenType::NonTerminal)
            result.append(token.value);
        else
            result.append(token.value);
    }
    return result;
}

vector<size_t> BNF_statement::find_all(const string& input, const string& query) {
    vector<size_t> positions;
    size_t pos = 0;
    while (true) {
        pos = input.find(query, pos);
        if (pos == string::npos) break;

        positions.push_back(pos);
        pos += query.size();
    }
    return positions;
}