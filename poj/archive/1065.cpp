/* 
 * POJ - 1065
 * minimize sets num of LISs.
 */
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    int t, n, l, w;
    vector<pair<int, int> > sticks;
    cin >> t;
    while(t) {
        sticks.clear();
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> l >> w;
            sticks.push_back(pair<int, int>(l,w));
        }
        sort(sticks.begin(), sticks.end());

        multiset<int> ws;
        vector<pair<int, int> >::iterator it = sticks.begin();
        while(it != sticks.end()) {
            multiset<int>::iterator ub = ws.upper_bound(it->second);
            if(ub != ws.begin()) {
                ub--;
                ws.erase(ub);
            }
            ws.insert(it->second);
            it++;
        }
        cout << ws.size() << endl;
        
        t--;
    }
    return 0;
}
