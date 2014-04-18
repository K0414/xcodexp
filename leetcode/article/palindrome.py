"""
This file demonstrates algorithms from these following articles:
    http://leetcode.com/2012/01/palindrome-number.html
    http://leetcode.com/2011/11/longest-palindromic-substring-part-i.html
    http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
"""

# For Is Palindrome.
IP_INPLACE = 1
IP_RECURSIVE = 2
# For Longest Palindrome Substring.
LPS_LCS = 11
LPS_MANACHER = 12
LPS_DP = 13
LPS_EXPANSION = 14


class Palindrome(object):

    def is_palindrome_number(self, num, method=IP_INPLACE):
        if num < 0:
            raise ValueError('Negtive number not supported.')
        if method == IP_INPLACE:
            return self._is_palindrome_inplace(num)
        elif method == IP_RECURSIVE:
            return self._is_palindrome_recursive(num, num)[0]
        else:
            raise ValueError('Invalid method value.')

    def _is_palindrome_inplace(self, num):
        div = 1
        while num / div:
            div *= 10
        div /= 10
        while div:
            l = num / div
            r = num % 10
            if (l != r):
                return False
            num = (num % div) / 10
            div /= 100
        return True

    def _is_palindrome_recursive(self, x, y):
        if x == 0:
            return True, y
        _, _y = self._is_palindrome_recursive(x/10, y)
        if _ and (x%10 == _y%10):
            return True, _y/10
        return False, None


    def longest_palindrome_substring(self, s, method=LPS_MANACHER):
        if method == LPS_MANACHER:
            return self._lps_manacher(s)
        elif method == LPS_LCS:
            return self._lps_lcs(s)
        elif method == LPS_EXPANSION:
            return self._lps_expansion(s)
        elif method == LPS_DP:
            return self._lps_dp(s)
        else:
            raise ValueError('Invalid method value.')

    def _lps_expansion(self, s):
        longest = ''
        for i in range(len(s)):
            for _ in [(i,i), (i,i+1)]:
                l, r = _
                while l >=0 and r < len(s):
                    if s[l] == s[r]:
                        if r-l+1 > len(longest):
                            longest = s[l:r+1]
                        l -= 1
                        r += 1
                    else:
                        break
        return longest

    def _lps_lcs(self, s):
        def lcs(a, b, cond=lambda L,l,i,j: True):
            # table[(i,j)] memoizes the lcs ends with a[i] and b[j].
            table = dict()
            longest = ''
            for i in range(len(a)):
                table[(i, 0)] = (a[i] == b[0]) and 1 or 0
                if a[i] == b[0]: longest = b[0]
            for j in range(len(b)):
                table[(0, j)] = (a[0] == b[j]) and 1 or 0
                if a[0] == b[i]: longest = a[0]
            for i in range(1, len(a)):
                for j in range(1, len(b)):
                    if a[i] == b[j]:
                        table[(i, j)] = table[(i-1, j-1)] + 1
                    else:
                        table[(i, j)] = 0
                    c = cond(len(a), table[(i, j)], i,  j)
                    if table[(i, j)] > len(longest) and c:
                        longest = a[i - table[(i, j)] + 1 : i+1]
            return longest

        def reverse(s):
            t = ''
            for i in range(len(s)-1, -1, -1):
                t += s[i]
            return t

        r = reverse(s)
        check = lambda L,l,i,j: L + l - 2 == i + j
        return lcs(s, r, check)

    def _lps_dp(self, s):

        # table[(i,j)] memoizes if s[i:j+1] is a palindrome.
        table = dict()
        longest = s and s[0] or ''

        for i in range(len(s)):
            table[(i, i)] = True

        for i in range(len(s)-1):
            table[(i, i+1)] = (s[i] == s[i+1])
            if table[(i, i+1)] and len(longest) < 2:
                longest = s[i:i+2]

        for d in range(2, len(s)):
            for i in range(len(s)-d):
                if s[i] == s[i+d] and table[(i+1, i+d-1)]:
                    table[(i, i+d)] = True
                    longest = s[i:i+d+1]
                else:
                    table[(i, i+d)] = False

        return longest

    def _lps_manacher(self, s):
        """Manacher algorithm is based on the expansion method and take advantage of
        the palindrome's symmetric property.

        @ivar P: A list of size 2*len(s)+1 to store the longest palindrome length
                 centered at each character (including the virtual character '#').

        @ivar C: Center of the current palindrome.

        @ivar R: Right bound of the palindrome centered at C.
        """
        ss = '\0' + '\0'.join(s) + '\0'
        P = [0] * len(ss)
        C = R = 0
        for i in range(1, len(ss)):
            i_mirror = C - (i - C)

            P[i] = R > i and min(P[i_mirror], R - i) or 0

            while (i - P[i] - 1 >= 0) and (i + P[i] + 1 < len(ss)) \
                    and (ss[i - P[i] - 1] == ss[i + P[i] + 1]):
                P[i] += 1

            if i + P[i] > R:
                R = i + P[i]
                C = i

        longest = s and s[0] or ''
        for i in range(1, len(ss)):
            if P[i] > len(longest):
                l = (i - P[i]) / 2
                r = l + P[i]
                longest = s[l:r]

        return longest
