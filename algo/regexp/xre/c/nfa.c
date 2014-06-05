#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *re2post(char *re)
{
    int natom, nalt;
    static char buf[8000];
    char *dst;
    struct {
        int natom;
        int nalt;
    } paren[100], *p;

    p = paren;
    dst = buf;
    natom = 0;
    nalt = 0;
    if (strlen(re) >= sizeof(buf)/2)
        return NULL;
    for (; *re; re++) {
        switch(*re) {
            case '(':
                if (natom > 1) {
                    --natom;
                    *dst++ = '.';
                }
                if (p >= paren+100)
                    return NULL;
                p->natom = natom;
                p->nalt = nalt;
                p++;
                natom = 0;
                nalt = 0;
                break;
            case '|':
                if (natom == 0)
                    return NULL;
                while(--natom > 0)
                    *dst++ = '.';
                nalt++;
                break;
            case ')':
                if (p == paren)
                    return NULL;
                if (natom == 0)
                    return NULL;
                while(--natom > 0)
                    *dst++ = '.';
                for(; nalt > 0; nalt--)
                    *dst++ = '|';
                p--;
                natom = p->natom;
                nalt = p->nalt;
                natom++;
                break;
            case '?':
            case '+':
            case '*':
                if (natom == 0)
                    return NULL;
                *dst++ = *re;
                break;
            default:
                if (natom > 1) {
                    *dst++ = '.';
                    natom--;
                }
                *dst++ = *re;
                natom++;
                break;
        }
    }
    if (p != paren)
        return NULL;
    while(--natom > 0)
        *dst++ = '.';
    for (; nalt > 0; nalt--)
        *dst++ = '|';
    *dst = '\0';
    return buf;
}

enum {
    Split = 256,
    Match = 257
};

int nstate;
typedef struct State State;
struct State {
    int c;
    State *out;
    State *out1;
    int lastlist;
};
State *state(int c, State *out, State *out1)
{
    State *s = (State *) malloc(sizeof(State));
    s->c = c;
    s->out = out;
    s->out1 = out1;
    s->lastlist = 0;
    nstate++;
    return s;
}
State matchstate = { Match };

typedef union Ptrlist Ptrlist;
union Ptrlist {
    Ptrlist *next;
    State *s;
};

typedef struct Frag Frag;
struct Frag {
    State *start;
    Ptrlist *outp;
};
Frag frag(State *start, Ptrlist *outp)
{
    Frag f = { start, outp };
    return f;
}

Ptrlist *list1(State **p)
{
    Ptrlist *l;

    l = (Ptrlist *) p;
    l->next = NULL;
    return l;
}

Ptrlist *append(Ptrlist *l1, Ptrlist *l2)
{
    Ptrlist *l = l1;
    while (l->next)
        l = l->next;
    l->next = l2;
    return l1;
}

void patch(Ptrlist *l, State *s)
{
    Ptrlist *next;

    for(; l; l = next) {
        next = l->next;
        l->s = s;
    }
}

State *post2nfa(char *postfix)
{
    char *p = postfix;
    State *s;
    Frag stack[1000], *sp, e, e1, e2;

    #define push(e) *sp++ = e
    #define pop()   *--sp

    sp = stack;
    for(; *p; p++) {
        switch(*p) {
            default:  /* char */
                s = state(*p, NULL, NULL);
                push(frag(s, list1(&s->out)));
                break;
            case '|':  /* alternate */
                e2 = pop();
                e1 = pop();
                s = state(Split, e1.start, e2.start);
                push(frag(s, append(e1.outp, e2.outp)));
                break;
            case '?':  /* zero or one */
                e = pop();
                s = state(Split, e.start, NULL);
                push(frag(s, append(e.outp, list1(&s->out1))));
                break;
            case '+':  /* one or more */
                e = pop();
                s = state(Split, e.start, NULL);
                patch(e.outp, s);
                push(frag(e.start, list1(&s->out1)));
                break;
            case '*':  /* zero or more */
                e = pop();
                s = state(Split, e.start, NULL);
                patch(e.outp, s);
                push(frag(s, list1(&s->out1)));
                break;
            case '.':  /* catenate */
                e2 = pop();
                e1 = pop();
                patch(e1.outp, e2.start);
                push(frag(e1.start, e2.outp));
                break;
        }
    }

    e = pop();
    if(sp != stack)
        return NULL;

    patch(e.outp, &matchstate);
    return e.start;
#undef push
#undef pop
}


typedef struct List List;
struct List {
    State **s;
    int n;
};
List l1, l2;
int listid;

void addstate(List *l, State *s);
void step(List *clist, int c, List *nlist);

List *startlist(State *start, List *l)
{
    l->n = 0;
    listid++;
    addstate(l, start);
    return l;
}

int ismatch(List *l)
{
    int i;
    for (i = 0; i < l->n; i++) {
        if (l->s[i] == &matchstate)
            return 1;
    }
    return 0;
}

void addstate(List *l, State *s)
{
    if (s == NULL || s->lastlist == listid)
        return;
    s->lastlist = listid;
    if (s->c == Split) {
        addstate(l, s->out);
        addstate(l, s->out1);
        return;
    }
    l->s[l->n++] = s;
}

void step(List *clist, int c, List *nlist)
{
    int i;
    listid++;
    nlist->n = 0;
    for (i = 0; i < clist->n; i++) {
        State *s = clist->s[i];
        if (s->c == c) {
            addstate(nlist, s->out);
        }
    }
}

int match(State *start, char *s)
{
    List *clist, *nlist, *t;

    clist = startlist(start, &l1);
    nlist = &l2;
    for (; *s; s++) {
        char c = *s & 0xFF;
        step(clist, c, nlist);
        t = clist; clist = nlist; nlist = t;
    }
    return ismatch(clist);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./nfa regexp string...\n");
        return 1;
    }

    char *post = re2post(argv[1]);
    if (post == NULL) {
        fprintf(stderr, "Invalid regexp.\n");
        return 1;
    }

    printf("postfix: %s\n", post);

    State *start = post2nfa(post);
    if (start == NULL) {
        fprintf(stderr, "Error in post2nfa.\n");
        return 1;
    }

    int i;
    l1.s = (State **) malloc(nstate * sizeof(l1.s[0]));
    l2.s = (State **) malloc(nstate * sizeof(l2.s[0]));
    for (i = 2; i < argc; i++) {
        if (match(start, argv[i]))
            printf("%s\n", argv[i]);
    }

    return 0;
}
