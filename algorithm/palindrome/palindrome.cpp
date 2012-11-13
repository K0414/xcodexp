#include <iostream>
#include <cstring>
using namespace std;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

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

int longest_palindrome_manacher(const char *str, int *pos = NULL)
{
    int len = strlen(str);
    int bound = (len << 1) + 1;
    int *rad = new int[bound];
    char *salted = new char[bound + 2];
    salted[0] = '$';
    salted[1] = '#';
    for(int i = 0; i < len; i++) {
        salted[(i << 1) + 2] = str[i];
        salted[(i << 1) + 3] = '#';
    }
    salted[bound + 1] = '\0';

    /*
     * mxlen - length of the longest palindrome.
     * mx    - right most visited character.
     */
    int mxlen, mxid, mx, id;
    id = 1; mxlen = mxid = mx = 0;
    for(int i = 1; salted[i]; i++) {
        if(mx > i) {
            rad[i] = MIN(rad[(id << 1) - i], mx - i);
        } else {
            rad[i] = 1;
        }

        while(str[i - rad[i]] == str[i + rad[i]]) {
            rad[i]++;
        }

        if(mx < i + rad[i]) {
            mx = i + rad[i];
            id = i;
        }

        if(mxlen < rad[i]) {
            mxlen = rad[i];
            mxid = i;
        }
    }

    mxlen -= (salted[mxid] == '#' ? 1 : 0);
    if(pos) {
        *pos = (mxid - mxlen) >> 1;
    }

    delete [] rad;
    delete [] salted;
    return mxlen;
}

int main(int argc, char *argv[])
{
    int start;

    if(argc == 2) {
        string str = argv[1];
        int start;
        int len = longest_palindrome_manacher(str.c_str(), &start);
        str = str.substr(start, len);
        cout << str << endl;
    } else {
        cout << argv[0] << " string" << endl;
    }
    return 0;
}
