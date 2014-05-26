#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string convert(string s, int nRows) {
        string ns = "";
        if (nRows == 1)
            return s;
        for (int r = 0; r < nRows; r++)
        {
            for (int i = 0; (2 * i * (nRows - 1) + r) < s.size(); i++)
            {
                ns += s[2 * i * (nRows - 1) + r];
                if (r > 0 && r < (nRows - 1) && (2 * (i + 1) * (nRows - 1) - r) < s.size()) 
                    ns += s[2 * (i + 1) * (nRows - 1) - r];
            }
        }
        return ns;
    }
};


int main()
{
    Solution sol;
    cout << sol.convert("PAYPALISHIRING", 3) << endl;
    string s;
    int n;
    while(cin>>n)
    {
        cin>>s;
        cout << sol.convert(s, n) << endl;
    }
    return 0;
}
