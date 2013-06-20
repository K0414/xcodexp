#include <string>
#include <vector>
#include "libstr.h"
using namespace std;

void preKmp(int tab[], string p)
{
    int i,j;

    i = 0;
    j = tab[0] = -1;
    while(i<p.size()) {
        while(j>-1 && p[i] != p[j])
            j = tab[j];
        i++;
        j++;
        if(p[i] == p[j])
            tab[i] = tab[j];
        else
            tab[i] = j;
    }
}

void KMP(string t, string p, vector<int>& res)
{
    int i,j;
    int *kmpNext = new int[p.size()+1];

    preKmp(kmpNext, p);
    i = j = 0;
    while(i<t.size()) {
        while(j > -1 && t[i] != p[j])
            j = kmpNext[j];
        i++;
        j++;
        if(j == p.size()) {
            res.push_back(i - j);
            j = kmpNext[j];
        }
    }

    delete [] kmpNext;
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
        KMP(s, p, res);
        for(int i=0; i<res.size(); i++)
            cout << res[i] << ' ';
        cout << endl;
    }
    return 0;
}
