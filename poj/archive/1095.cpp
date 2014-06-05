/* 
 * POJ - 1095
 * A binary tree structure make a (L * Base^1 + R * Base^0) form,
 * where Base is *elems_count of right child nodes*.
 */
#include <iostream>
#include <vector>
using namespace std;

vector<int> elems_count;

string gentree(int num)
{
    if (num == 0) return "";

    // count nodes
    int upper_bound, lower_bound, nodes;
    lower_bound = upper_bound = nodes = 0;
    while (upper_bound < num) {
        lower_bound = upper_bound + 1;
        nodes++;
        upper_bound += elems_count[nodes];
    }
    int lbroot = lower_bound;

    // count left child nodes
    int lnodes = 0;
    upper_bound = lbroot + elems_count[lnodes]*elems_count[nodes-lnodes-1] - 1;
    while(upper_bound < num) {
        lower_bound = upper_bound + 1;
        lnodes++;
        upper_bound += elems_count[lnodes]*elems_count[nodes-lnodes-1];
    }
    int lbleft = lower_bound;
    
    int rnodes = nodes - lnodes - 1;
    int lindex = (num - lbleft) / elems_count[rnodes];
    int rindex = (num - lbleft) % elems_count[rnodes];
    int loffset, roffset;
    loffset = roffset = 0;
    for(int i = 0; i < lnodes; i++) loffset += elems_count[i];
    for(int i = 0; i < rnodes; i++) roffset += elems_count[i];
    string left = gentree(loffset + lindex);
    string right = gentree(roffset + rindex);
    if (left.size() > 0) left = "(" + left + ")";
    if (right.size() > 0) right = "(" + right + ")";

    return left + "X" + right;
}

int main()
{
    elems_count.push_back(1);
    int total = 0;
    for(int n = 1; ; n++) {
        if(total >= 500000000) break;
        int cnt = 0;
        for(int i = 0; i < n; i++) cnt += elems_count[i] * elems_count[n-i-1];
        elems_count.push_back(cnt);
        total += cnt;
    }

    int N;
    while(cin >> N)
    {
        if(N == 0) break;
        string res = gentree(N);
        cout << res << endl;
    }
    return 0;
}
