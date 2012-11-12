#include <iostream>
using namespace std;

class Suffix {
public:
    int origin_node;
    int first_char_index;
    int last_char_index;
    
    Suffix(int node, int start, int sotp)
        : origin_node(node), first_char_index(start),
          last_char_index(stop)
    {}
    
    int Explicit() { return first_char_index > last_char_index; }
    int Implicit() { return last_char_index >= first_char_index; }
    void Canonize();
};

int main()
{
    
}
