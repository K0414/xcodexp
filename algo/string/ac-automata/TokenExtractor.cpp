#include <iostream>
#include <cstring>
#include <queue>
#include "TokenExtractor.h"
using namespace std;

// TODO: handle alloc memory failed case.
///////////////////////////////////////////////////////////////

TNode::TNode(char c)
{
    this->c = c;
    next = fail = NULL;
    patt_type = patt_len = 0;
    memset(cn, 0, sizeof(cn));
}

TNode::~TNode()
{
    for (int i = 0; i < n_slots; i++) {
        TNode *p = cn[i];
        while(p) {
            TNode *t = p;
            p = p->next;
            delete t;
        }
    }
}

void TNode::add_pattern(const char *pat, int type)
{
    const char *p = pat;
    TNode *nn, *n = this;
    while(*p) {
        nn = n->get_child(*p);
        if(nn == NULL) {
            nn = new TNode(*p);
            nn->next = n->cn[(unsigned char)*p % n_slots];
            n->cn[(unsigned char)*p % n_slots] = nn;
        }
        n = nn;
        p++;
    }
    n->patt_type = type;
    n->patt_len  = p - pat;
}

void TNode::make_fail_links()
{
    queue<TNode*> q;
    /* pn: pnode, pl: plink(fail), pc: pchild */
    TNode *pn, *pl, *pc;

    q.push(this);
    while(!q.empty()) {
        pn = q.front();
        q.pop();
        for (int i = 0; i < n_slots; i++) {
            pc = pn->cn[i];
            while(pc) {
                pl = pn->fail;
                while(pl && pl->get_child(pc->c) == NULL) {
                    pl = pl->fail;
                }
                if(pl) {
                    pc->fail = pl->get_child(pc->c);
                } else {
                    pc->fail = this;
                }
                q.push(pc);
                pc = pc->next;
            }
        }
    }
}

char *TNode::match(const char *buf, int len, int &type, TNode* &node)
{
    const char *p = buf;
    TNode *nn, *n = this;
    for (int i = 0; i < len; i++) {
        nn = n->get_child(p[i]);
        if(nn) {
            if(nn->patt_type != 0) {
                type = nn->patt_type;
                node = this;
                while(node->fail)
                    node = node->fail;
                return const_cast<char*>(p + i + 1);
            }
            n = nn;
        } else {
            while(n && n->fail && n->get_child(p[i]) == NULL)
                n = n->fail;
            if(n->get_child(p[i]))
                n = n->get_child(p[i]);
        }
    }
    node = n;
    type = 0;
    return NULL;
}

TNode *TNode::get_child(char c)
{
    /* residual of a negtive number is NEGTIVE. */
    TNode *p = cn[(unsigned char)c % n_slots];
    while(p) {
        if(p->c == c)
            return p;
        p = p->next;
    }
    return NULL;
}

///////////////////////////////////////////////////////////////

TokenAnalyzer::TokenAnalyzer() : m_matcher(NULL)
{
}

TokenAnalyzer::~TokenAnalyzer()
{
}

/* 
 * Usage:
 *   1. TokenMatcher  *matcher    = TokenAnalyzer::CreateMatcher(cmd_list);
 *   2. TokenAnalyzer *analyzer   = new TokenAnalyzer;
 *   3. analyzer->Init(matcher);
 *   4. analyzer->Match(...);
 *
 * A matcher can be used by multiple analyzers.
 */
TokenMatcher *TokenAnalyzer::CreateMatcher(TokenID *cmd_list)
{
    TokenMatcher *matcher = new TokenMatcher(0x0);
    TokenID *l = cmd_list;
    while(l->token) {
        matcher->add_pattern(l->token, l->id);
        l++;
    }
    matcher->make_fail_links();
    return matcher;
}

void TokenAnalyzer::Init(TokenMatcher *matcher)
{
    m_matcher = matcher;
}

/*
 * Look for command tokens in buffer.
 * 
 * @param pData     pointer to buffer.
 * @param nDataLen  buffer length.
 * @param nCmdType  return command type, 0 when not found.
 * @return          return NULL or the start index of the command found.
 */
char *TokenAnalyzer::Match(const char *pData, int nDataLen, int &nCmdType)
{
    if(m_matcher == NULL)
        return NULL;

    TNode *next_matcher = NULL;
    char *p = m_matcher->match(pData, nDataLen, nCmdType, next_matcher);
    if(p) {
        m_matcher = next_matcher;
        return p;
    }

    m_matcher = next_matcher;
    return NULL;
}

