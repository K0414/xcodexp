#include <string>
#include <vector>
#include "libstr.h"
using namespace std;

#define SEP '\xFF'

int right_most(string s, int pos)
{
    int end = pos;
    while(end < s.size()) {
        if(s[end-pos] != s[end])
            break;
        end++;
    }
    return end - 1 > pos ? end - 1 : pos;
}

void z_algo(string t, string p, vector<int>& res)
{
    string s = p + (char)SEP + t;
    int c,b,l,r,*z = new int[p.size()+1];

    r = right_most(s, 1);
    l = 1;
    z[1] = r - l + 1;
    for(int i=2; i<s.size(); i++)
    {
        if(i>r) {
            r = right_most(s, i);
            l = i;
            c = r - i + 1;
            if(i<p.size())
                z[i] = c;
            if(c == p.size() && s[i] == p[0]/* for single char pattern */)
                res.push_back(i - p.size() - 1);
        } else {
            b = r - i + 1;
            if(b>z[i-l]) {
                r = right_most(s, r);
                l = i;
                c = r - l + 1;
                if(i<p.size())
                    z[i] = c;
                if(c == p.size() && s[i] == p[0]/* for single char pattern */)
                    res.push_back(i - p.size() - 1);
            } else {
                c = z[i-l];
                if(i<p.size())
                    z[i] = c;
                if(c == p.size() && s[i] == p[0]/* for single char pattern */)
                    res.push_back(i - p.size() - 1);
            }
        }
//        cout << "z[" << i << "]:" << c << " l:" << l << " r:" << r << endl;
    }
    delete [] z;
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
