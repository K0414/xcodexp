#include <iostream>
#include <cstring>
using namespace std;

class UnionFind {
public:
    UnionFind(int size) : _size(size), _father(NULL), _rank(NULL)
    {
        _father = new int[_size];
        _rank = new int[_size];
        memset(_rank, 0, sizeof(int) * _size);
        for(int i=0; i<_size; i++)
            _father[i] = i;
    }
    virtual ~UnionFind()
    {
        if(_father)
            delete [] _father;
        if(_rank)
            delete [] _rank;
    }
    void join(int ia, int ib);
    int find(int idx);
private:
    UnionFind() {}
    int _get_father(int idx);
    int _size;
    int *_father;
    int *_rank;
};

int UnionFind::_get_father(int idx)
{
    if(idx != _father[idx])
        _father[idx] = _get_father(_father[idx]);
    return _father[idx];
}

void UnionFind::join(int ia, int ib)
{
    int fx,fy;
    fx = _get_father(ia);
    fy = _get_father(ib);
    if(_rank[fx] > _rank[fy]) {
        _father[fy] = fx;
    } else {
        _father[fx] = fy;
        if(_rank[fx] == _rank[fy])
            _rank[fy]++;
    }
}

int UnionFind::find(int idx)
{
    return _get_father(idx);
    return false;
}

int main()
{
    UnionFind uf(15);
    uf.join(5,8);
    uf.join(7,8);
    for(int i=0; i<15; i++) {
        cout << uf.find(i) << endl;
    }
    return 0;
}
