#ifndef __RTSP_ANALYZER__
#define __RTSP_ANALYZER__

struct TokenID {
    const char   *token;
    int           id;
};

class TNode {
public:
    static const int n_slots = 4;

    TNode(char c);
    ~TNode();

    void add_pattern(const char *pat, int type);
    void make_fail_links();
    char *match(const char *buf, int len, int &type, TNode* &node);

private:
    TNode();
    TNode          *get_child(char c);
    TNode*          cn[n_slots];
    char            c;
    TNode          *next;
    TNode          *fail;

    int             patt_type;
    int             patt_len;
};

typedef TNode TokenMatcher;

class TokenAnalyzer {
public:
    TokenAnalyzer();
    ~TokenAnalyzer();

    static TokenMatcher *CreateMatcher(TokenID *cmd_list);

    void Init(TokenMatcher *matcher);
    char *Match(const char *pData, int nDataLen, int &nCmdType);

private:
    TNode   *m_matcher;
};

#endif /* __RTSP_ANALYZER__ */
