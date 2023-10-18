// <assign> -> <id>=<expr>
// <id> -> A|B|C|D
// <expr> -> <expr> - <term> | <id>
// <term> -> <term> * <factor> | <term>/<factor> | <factor>
// <factor> -> (<expr>) | <id>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "bnf.h"
using namespace std;

int main() {
    vector<string> inputs;
    string BNF = "";
    BNF.append("<assign> -> <id>=<expr>\n");
    BNF.append("<id> -> A|B|C|D\n");
    BNF.append("<expr> -> <expr> - <term> | <id>\n");
    BNF.append("<term> -> <term> * <factor> | <term>/<factor> | <factor>\n");
    BNF.append("<factor> -> (<expr>) | <id>\n");

    BNF_statement bnf(BNF);

    inputs.push_back("A=B-C/A-A");
    inputs.push_back("A=B*C/D-A");
    inputs.push_back("A=B/(C-A)");
    inputs.push_back("A=B-(C*A)");
    inputs.push_back("A=B*(D-A)");

    inputs.push_back("A=A-B-C");

    for (auto input : inputs)
        cout << (bnf.is_valid(input) ? input + " is VAILD" : input + " is INVAILD") << endl
             << endl;
    return 0;
}
