#include <string>
#include <vector>
#include "libstr.h"
using namespace std;

/* 
 * boyer_moore algorithm:
 * 1) right-to-left match 
 * 2) bad character rule
 * 3) good-prefix rule
 * */
void boyer_moore(string t, string p, vector<int>& res)
{
    // preprocessing stage
    // compute Right-Most- and l'(i)

    // search stage
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

