#include <iostream>
#include <cstring>
using namespace std;

/*
 * return value is the length of the longest palindrome,
 * pos(optional) points to the start of the palindrome.
 */
int longest_palindrome_naive(const char *str, int *pos = NULL)
{
    int max = 0;
    int len = strlen(str);
    int bound = len + len - 1;

    for(int i = 0; i < bound; i++) {
        int l = i / 2;
        int r = l + i % 2;

        while(l >= 0 && r < len && str[l] == str[r]) {
            l--;
            r++;
        }
        if(max < r - l - 1) {
            max = r - l - 1;
            if(pos)
                *pos = l + 1;
        }
    } 

    return max;
}

/*
 * return value is the length of the longest palindrome,
 * pos(optional) points to the start of the palindrome.
 */
int longest_palindrome(const char *str, int *pos = NULL)
{
    int k;
    int max = 0;
    int len = strlen(str);
    int bound = len + len - 1;
    int *palen = new int[bound];
    memset(palen, 0, sizeof(int) * bound);

    for(int i = 0; i < bound; i++) {
        int l = i / 2 - palen[i] / 2;
        int r = l + i % 2 + palen[i] / 2;

        while(l >= 0 && r < len && str[l] == str[r]) {
            l--;
            r++;
        }

        /* update palen[i + k], for k = 1 to as long as possible. */
        palen[i] = r - l - 1;
        if(max < palen[i]) {
            max = palen[i];
            if(pos)
                *pos = l + 1;
        }
        for(k = 1; k <= palen[i] / 2; k++) {
            palen[i + k] = palen[i - k];
            if(i - k - palen[i - k] / 2 <= i - palen[i] / 2) {
                i += k - 1;
                break;
            }
        }
    } 

    delete [] palen;
    return max;
}

int main(int argc, char *argv[])
{
    int start;

    if(argc == 2) {
        string str = argv[1];
        int start;
        int len = longest_palindrome_naive(str.c_str(), &start);
        str = str.substr(start, len);
        cout << str << endl;
        len = longest_palindrome(str.c_str(), &start);
        str = str.substr(start, len);
        cout << str << endl;
    } else {
        cout << argv[0] << " string" << endl;
    }
    return 0;
}
