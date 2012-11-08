#include <iostream>
using namespace std;

int longest_palindrome(const char *str)
{

return -1;
}

int main(int argc, char *argv[])
{
    if(argc == 2) {
        string str = argv[1];
        cout << longest_palindrome(str.c_str()) << endl;
    } else {
        cout << argv[0] << " string" << endl;
    }
    return 0;
}
