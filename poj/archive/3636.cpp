/* 
 * POJ - 3636
 * note: cin is slower than scanf
 */
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
    int t, n, l, w;
    vector<pair<int, int> > dolls;
    scanf("%d", &t);
    while(t) {
        dolls.clear();
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &l, &w);
            dolls.push_back(pair<int, int>(l,w));
        }
        sort(dolls.begin(), dolls.end());

        multiset<int> ws;
        vector<pair<int, int> >::iterator it = dolls.begin();
        while(it != dolls.end()) {
            vector<pair<int, int> >::iterator end;
            for(end = it; end != dolls.end() && end->first == it->first; end++);

            vector<int> buf;
            while(it != end) {
                buf.push_back(it->second);
                multiset<int>::iterator lb = ws.lower_bound(it->second);
                if(lb != ws.begin()) {  // larger than the smallest
                    lb--;
                    ws.erase(lb);
                }
                it++;
            }
            ws.insert(buf.begin(), buf.end());
        }
        cout << ws.size() << endl;
        
        t--;
    }
    return 0;
}
