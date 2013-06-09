#include <string>
#include <vector>
#include <queue>
#include "libstr.h"
using namespace std;



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
