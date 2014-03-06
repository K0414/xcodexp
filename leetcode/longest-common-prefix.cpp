#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1) return strs[0];

        sort(strs.begin(), strs.end());
        int min_len = strs.front().size();
        string prefix = "";
        for (int i = 0; i < strs.size(); i++)
            min_len = min(min_len, (int)strs[i].size());
        const string& first = strs.front();
        const string& last = strs.back();
        for (int i = 0; i < min_len; i++)
        {
            if (first[i] == last[i])
                prefix += first[i];
            else
                break;
        }
        return prefix;
    }
};

int main()
{
    Solution sol;
    int n;
    cin >> n;
    vector<string> strs;
    string s;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        strs.push_back(s);
    }
    cout << sol.longestCommonPrefix(strs) << endl;
    return 0;
}
