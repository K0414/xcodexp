namespace xre {

class XRegExp {
public:
private:
    char *re2post(const char *re);
    
    /* Define structures that represent NFAs. */
    struct State {
        int      c;
        State   *out;
        State   *out1;
        int      lastlist;
    };
    union Ptrlist {
        State   *s;
        Ptrlist *next;
    };
    struct Frag {
        State   *start;
        Ptrlist *outp;
    };
    /* NFA construction functions. */
    Ptrlist *append(Ptrlist *l1, Ptrlist *l2);
    void patch(Ptrlist *l, State *s);
    State *post2nfa(const char *s);

    /* Lists that hold NFA states, built on-the-fly. */
    struct List {
        State **s;
        int     n;
    };
    List *startlist(State **outp);
    void addstate(List *l, State *s);
    void step(List *clist, int c, List *nlist);
    int ismatch(List *l);
    int match(State *start, const char *s);

    int nstate;
    int lastid;
};

}
