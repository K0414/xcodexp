#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include "libstr.h"
using namespace std;

class TNode {
public:
    static const int n_slots = 4;
    TNode* cn[n_slots];
    char c;
    TNode *next;
    bool isend;

    TNode(char c)
    {
        this->c = c;
        memset(this->cn, 0, n_slots * sizeof(TNode*));
        this->next = NULL;
        this->isend = false;
    }
    ~TNode() {}
    void add_pattern(string s);
    bool match(string s);
private:
    void insert(string s);
    TNode *get_child(char c);
};

TNode *TNode::get_child(char c)
{
    TNode *p = cn[c % n_slots];
    if(p == NULL)
        return NULL;
    while(p) {
        if(p->c == c)
            return p;
        p = p->next;
    }
}

void TNode::insert(string s)
{
    if(s.size() <= 0) return;
    TNode *p = get_child(s[0]);
    if(p == NULL) {
        TNode *nn = new TNode(s[0]);
        int i = s[0] % n_slots;
        if(cn[i] == NULL) {
            cn[i] = nn;
        } else {
            p = cn[i];
            while(p->next)
                p = p->next;
            p->next = nn;
        }
        p = nn;
    }
    
    if(s.size() > 1)
        p->insert(s.substr(1));
    else
        p->isend = true;
}



int main()
{
    string s, p;
    while(true) {
        TNode trie('^');
        cout << "insert: ";
        cin >> s;
        while(s != "#") {
            trie.insert(s);
            cout << "insert: ";
            cin >> s;
        }
        cout << "search: ";
        cin >> p;
        while(p != "#") {
            cout << (trie.contains(p) ? "True" : "False") << endl;
            cout << "search: ";
            cin >> p;
        }
        cout << endl;
    }
    return 0;
}
