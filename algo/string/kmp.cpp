#include <string>
#include <vector>
#include "libstr.h"
using namespace std;

void preKmp(int tab[], string p)
{
}

void KMP(string t, string p, vector<int>& res)
{
    int *kmpNext = new int[p.size()+1];

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
