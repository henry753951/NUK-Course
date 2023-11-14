// <assign> -> <id>=<expr>
// <id> -> A|B|C|D
// <expr> -> <expr> - <term> | <id>
// <term> -> <term> * <factor> | <term>/<factor> | <factor>
// <factor> -> (<expr>) | <id>
#include <iostream>

#include "bnf.h"
using namespace std;

int main() {
    vector<string> inputs;
    string BNF = "";

    // 輸入規則
    BNF.append("<assign> -> <id>=<expr>\n");
    BNF.append("<id> -> A|B|C|D\n");
    BNF.append("<expr> -> <expr> - <term> | <id>\n");
    BNF.append("<term> -> <term> * <factor> | <term>/<factor> | <factor>\n");
    BNF.append("<factor> -> (<expr>) | <id>\n");

    BNF_statement bnf(BNF);

    // 輸入測資
    inputs.push_back("A=B-C/A-A");
    inputs.push_back("A=B*C/D-A");
    inputs.push_back("A=B/(C-A)");
    inputs.push_back("A=B-(C*A)");
    inputs.push_back("A=B*(D-A)");
    inputs.push_back("A=B-(C-A)");
    inputs.push_back("A=(A-B(D-C))");

    // 輸出結果
    for (auto input : inputs)
        cout << (bnf.is_valid(input) ? input + " is VALID" : input + " is INVALID") << endl
             << endl;
    return 0;
}
