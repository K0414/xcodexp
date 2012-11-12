#include <iostream>
#include <cstring>
#include <string>
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
    int k, max = 0;
    int len = strlen(str);
    int bound = len + len + 1;
    int *palen = new int[bound];
    memset(palen, 0, sizeof(int) * bound);
    char *salted = new char[bound];
    k = 0;
    for(int i = 0; i < len; i++) {
        salted[k++] = ' ';
        salted[k++] = str[i];
    }
    salted[k] = ' ';

    for(int i = 0; i < bound; i++) {
        int l, r;
        l = r = i;
        while(l >= 0 && r < bound && salted[l] == salted[r]) {
            l--;
            r++;
        }
        palen[i] = r - l - 1;
        if(palen[i] > max) {
            max = palen[i];
            if(pos) {
                *pos = (l + 1) >> 1;
            }
        }
        /* the suffix, no need to check followers. */
        if(r == bound)
            break;

        for(int k = 1; k <= (palen[i] >> 1); k++) {
            if(i - k - (palen[i - k] >> 1) > i - (palen[i] >> 1)) {
                palen[i + k] = palen[i - k];
            } else {
                palen[i + k] = palen[i] - (k << 1) - 2;
                i += k - 1;
                break;
            }
        }       
    }
    /*
       for(int i = 0; i < bound; i++) {
       cout << palen[i] << ' ';
       }
       cout << endl;
     */
    delete [] palen;
    return (max >> 1);
}

int main(int argc, char *argv[])
{
    int start, i = 0;
    string str;

    while(cin >> str) {
        if(str == "END")
            break;

        int len = longest_palindrome(str.c_str(), &start);
        cout << "Case " << ++i << ": " << str.substr(start, len) << endl;
    }
    return 0;
}
