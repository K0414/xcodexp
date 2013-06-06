#include <string>
#include <vector>
#include "libstr.h"
using namespace std;

/* 
 * 3 strategies that makes boyer_moore algorithm fast:
 * 1) right-to-left match 
 * 2) bad character rule
 * 3) good-prefix rule
 * */
void boyer_moore(string t, string p, vector<int>& res)
{
    // preprocessing stage
    // 1) R[c]:  right-most occurance of each c in charset
    // 2) L'[i]: the right-most copy of P[i..n] in P[1..i-1] and P[i-1] differs
    // 3) l'[i]: the longest index of prefix that matches the suffix of P
    int R[256] = {0};
    for(int i=0; i<t.size(); i++)
    {
        R[(int)t[i]] = i;
    }
    int *N = new int[p.size()];
    int *L = new int[p.size()];
    int *l = new int[p.size()];
    for(int j=0; j<p.size(); j++)
    {
        int k = j;
        while(k && p[k] == p[p.size()-k-1]) k--;
        N[j] = j - k + 1;
    }
    for(int j=0; j<p.size(); j++)
    {
        
    }

    // search stage
    
    
    delete [] L;
    delete [] l;
}

int main()
{
    string s, p;
    vector<int> res;
    while(true) {
        cout << "text: " << endl;
        cin >> s;
        cout << "pattern: " << endl;
        cin >> p;
        res.clear();
        z_algo(s, p, res);
        for(int i=0; i<res.size(); i++)
            cout << res[i] << ' ';
        cout << endl;
    }
    return 0;
}

