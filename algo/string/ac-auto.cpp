#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include "libstr.h"
#include <assert.h>
using namespace std;

typedef pair<int, int> MatchResult;

class TNode {
public:
    static const int n_slots = 4;

    TNode(char c)
    {
        this->c = c;
        memset(this->cn, 0, n_slots * sizeof(TNode*));
        this->next = this->parent = this->fail = NULL;
        this->n_patts = this->patno = 0;
    }
    ~TNode()
    {
        TNode *p, *t;
        for(int i=0; i<n_slots; i++) {
            if(cn[i]) {
                p = cn[i];
                while(p) {
                    t = p;
                    p = p->next;
                    delete t;
                }
            }
        }
    }
    void add_pattern(string s);
    void make_fail_links();
    bool match(string s, vector<MatchResult>& res);
    string get_pattern(int idx);
private:
    TNode *get_child(char ch);
    queue<TNode*> q_nodes;
    vector<string> v_patts;
    TNode* cn[n_slots];
    char c;
    TNode *next;
    TNode *parent;
    TNode *fail;
    int n_patts;
    int patno;
};

TNode *TNode::get_child(char ch)
{
    TNode *p = cn[ch % n_slots];
    while(p) {
        if(p->c == ch)
            return p;
        p = p->next;
    }
    return NULL;
}

string TNode::get_pattern(int idx)
{
    if(0 < idx && idx <= n_patts)
        return v_patts[idx-1];
    return "";
}

void TNode::add_pattern(string s)
{
    v_patts.push_back(s);

    TNode *p, *pc;
    p = this;
    for(int i=0; i<s.size(); i++) {
        pc = p->get_child(s[i]);
        if(pc == NULL) {
            pc = new TNode(s[i]);
            pc->parent = p;
            int idx = s[i] % n_slots;
            if(p->cn[idx] == NULL) {
                p->cn[idx] = pc;
            } else {
                TNode *t = p->cn[idx];
                while(t->next)
                    t = t->next;
                t->next = pc;
            }
        }
        p = pc;
    }
    p->patno = ++n_patts;
}

void TNode::make_fail_links()
{
    if(this->fail) return;

    /* pn <-> pnode, pp <-> pparent, pl <-> plink(fail), pc <->pchild */
    TNode *p, *pn, *pp, *pl, *pc;
    this->fail = this;
    q_nodes.push(this);
    while(!q_nodes.empty()) {
        pn = q_nodes.front();
        q_nodes.pop();
        for(int i=0; i<n_slots; i++) {
            pc = pn->cn[i];
            while(pc) {
                pl = pn->fail;
                while(pl->get_child(pn->c) == NULL && pl != this) {
                    pl = pl->fail;
                }
                p = pl->get_child(pc->c);
                if(p) {
                    pc->fail = p;
                } else {
                    pc->fail = this;
                }
                q_nodes.push(pc);
                pc = pc->next;
            }
        }
    }
}

bool TNode::match(string s, vector<MatchResult>& res)
{
    make_fail_links();

    MatchResult r;
    TNode *p, *pn = this;
    for(int i=0; i<s.size(); i++) {
        p = pn->get_child(s[i]);
        if(p) {
            if(p->patno != 0) {
                r.first = i;
                r.second = p->patno;
                res.push_back(r);
                p = p->fail;
            }
            pn = p;
        } else {
            while(!pn->fail->get_child(s[i]) && pn->fail != this)
                pn = pn->fail;
        }
    }
    return res.empty();
}

int main()
{
    string s, p;
    vector<MatchResult> res;
    vector<string> patterns;
    while(true) {
        TNode acauto('^');
        cout << "add pattern: ";
        cin >> s;
        while(s != "#") {
            patterns.push_back(s);
            acauto.add_pattern(s);
            cout << "add pattern: ";
            cin >> s;
        }
        cout << "search: ";
        cin >> p;
        while(p != "#") {
            if(acauto.match(p, res)) {
                cout << res.size() << endl;
            } else {
                cout << "Not Found." << endl;
            }
            cout << "search: ";
            cin >> p;
        }
        cout << endl;
    }
    return 0;
}

