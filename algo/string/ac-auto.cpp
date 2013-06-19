#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include "libstr.h"
using namespace std;

class TNode {
public:
    static const int n_slots = 4;

    TNode(char c)
    {
        this->c = c;
        memset(this->cn, 0, n_slots * sizeof(TNode*));
        this->next = this->parent = this->fail = NULL;
        this->isend = false;
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
    bool match(string s, vector<int>& res);
private:
    TNode *get_child(char c);
    queue<TNode*> q_nodes;
    TNode* cn[n_slots];
    char c;
    TNode *next;
    TNode *parent;
    TNode *fail;
    bool isend;
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

void TNode::add_pattern(string s)
{
    if(s.size() <= 0) return;
    TNode *p = get_child(s[0]);
    if(p == NULL) {
        TNode *nn = new TNode(s[0]);
        nn->parent = this;
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
        p->add_pattern(s.substr(1));
    else
        p->isend = true;
}

void TNode::make_fail_links()
{
    /* pn <-> pnode, pp <-> pparent, pl <-> plink(fail) */
    TNode *p, *pn, *pp, *pl;
    this->fail = this;
    q_nodes.push(this);
    while(!q_nodes.empty()) {
        pn = q_nodes.front();
        q_nodes.pop();
        for(int i=0; i<n_slots; i++) {
            TNode *ps = cn[i];
            while(ps) {
                pp = ps->parent;
                if(pp && pp != this) {
                    pl = pp->fail;
                    while(pl->get_child(pn->c) == NULL && pl != this) {
                        pl = pl->fail;
                    }
                    p = pl->get_child(pn->c);
                    if(p) {
                        pn->fail = p;
                    } else {
                        pn->fail = this;
                    }
                }
                q_nodes.push(ps);
                ps = ps->next;
            }
        }
    }
}


bool TNode::match(string s, vector<int>& res)
{
    return ;
}		/* -----  end of function TNode::match  ----- */

int main()
{
    string s, p;
    vector<int> res;
    while(true) {
        TNode acauto('^');
        cout << "add pattern: ";
        cin >> s;
        while(s != "#") {
            acauto.add_pattern(s);
            cout << "add pattern: ";
            cin >> s;
        }
        cout << "search: ";
        cin >> p;
        while(p != "#") {
            if(acauto.match(p, res)) {

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
