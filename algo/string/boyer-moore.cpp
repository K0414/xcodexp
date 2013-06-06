#include <string>
#include <vector>
#include "libstr.h"
using namespace std;

#define ASIZE 256

/* bad character */
void make_delta1(int *tab, string p)
{
    const int NOT_FOUND = p.size();
    for(int i=0; i<ASIZE; i++)
    {
        tab[i] = NOT_FOUND;
    }
    for(int i=0; i<p.size(); i++)
    {
        tab[(int)p[i]] = i;
    }
}

int is_prefix(string p, int idx)
{
    int suffix_len = p.size() - idx;
    for(int i=0; i<suffix_len; i++)
    {
        if(p[i] != p[idx+i])
            return 0;
    }
    return 1;
}

int suffix_length(string p, int idx)
{
    int i;
    for(i=0; i<idx && p[idx-i] == p[p.size()-i-1]; i++);
    return i;
}

/* good prefix */
void make_delta2(int *tab, string p)
{
    int last_prefix_index = p.size()-1;
    for(int i=p.size()-1; i>=0; i++)
    {
        /* once a mismatch found, last_prefix_index never change again? */
        if(is_prefix(p, i))
            last_prefix_index = i;
        tab[i] = last_prefix_index + ;
    }
}

/* 
 * three strategies that makes boyer_moore algorithm fast:
 * 1) right-to-left match 
 * 2) bad character rule
 * 3) good-prefix rule
 * */
void boyer_moore(string t, string p, vector<int>& res)
{
    // preprocessing stage

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

