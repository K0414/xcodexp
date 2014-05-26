#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> stk;
        for ( int i = 0; i < tokens.size(); i++) {
            if (tokens[i][0] == '+' && tokens[i].size() == 1) {
                int b = stk.top();
                stk.pop();
                int a = stk.top();
                stk.pop();
                stk.push(a + b);
            } else if (tokens[i][0] == '-' && tokens[i].size() == 1) {
                int b = stk.top();
                stk.pop();
                int a = stk.top();
                stk.pop();
                stk.push(a - b);
            } else if (tokens[i][0] == '*') {
                int b = stk.top();
                stk.pop();
                int a = stk.top();
                stk.pop();
                stk.push(a * b);
            } else if (tokens[i][0] == '/') {
                int b = stk.top();
                stk.pop();
                int a = stk.top();
                stk.pop();
                stk.push(a / b);
            } else {
                stk.push(strtol(tokens[i].c_str(), NULL, 10));
            }
        }
        return stk.top();
    }
};

int main()
{
    vector<string> tokens;
    tokens.push_back("4");
    tokens.push_back("-2");
    tokens.push_back("/");
    tokens.push_back("2");
    tokens.push_back("-3");
    tokens.push_back("-");
    tokens.push_back("-");

    Solution sol;
    cout << sol.evalRPN(tokens) << endl;
    return 0;
}
