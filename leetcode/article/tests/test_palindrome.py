from palindrome import Palindrome, LPS_DP, LPS_LCS, LPS_EXPANSION, LPS_MANACHER
from nose.tools import assert_equal

s = 'FourscoreandsevenyearsagoourfaathersbroughtforthonthiscontainentanewnationconceivedinzLibertyanddedicatedtothepropositionthatallmenarecreatedequalNowweareengagedinagreahtcivilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth'
r = 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa'

class TestPalindrome(object):

    def test_lps_lcs(self):
        p = Palindrome()
        assert_equal(p.longest_palindrome_substring('', LPS_LCS), '')
        assert_equal(p.longest_palindrome_substring('a', LPS_LCS), 'a')
        assert_equal(p.longest_palindrome_substring('ab', LPS_LCS), 'a')
        assert_equal(p.longest_palindrome_substring('abc', LPS_LCS), 'a')
        assert_equal(p.longest_palindrome_substring('ababa', LPS_LCS), 'ababa')
        assert_equal(p.longest_palindrome_substring('abaaba', LPS_LCS), 'abaaba')
        assert_equal(p.longest_palindrome_substring('abcfgcba', LPS_LCS), 'a')
        assert_equal(p.longest_palindrome_substring(s, LPS_LCS), 'ranynar')
        assert_equal(p.longest_palindrome_substring(r, LPS_LCS), r)

    def test_lps_dp(self):
        p = Palindrome()
        assert_equal(p.longest_palindrome_substring('', LPS_DP), '')
        assert_equal(p.longest_palindrome_substring('a', LPS_DP), 'a')
        assert_equal(p.longest_palindrome_substring('ab', LPS_DP), 'a')
        assert_equal(p.longest_palindrome_substring('abc', LPS_DP), 'a')
        assert_equal(p.longest_palindrome_substring('ababa', LPS_DP), 'ababa')
        assert_equal(p.longest_palindrome_substring('abaaba', LPS_DP), 'abaaba')
        assert_equal(p.longest_palindrome_substring('abcfgcba', LPS_DP), 'a')
        assert_equal(p.longest_palindrome_substring(s, LPS_DP), 'ranynar')
        assert_equal(p.longest_palindrome_substring(r, LPS_DP), r)

    def test_lps_expansion(self):
        p = Palindrome()
        assert_equal(p.longest_palindrome_substring('', LPS_EXPANSION), '')
        assert_equal(p.longest_palindrome_substring('a', LPS_EXPANSION), 'a')
        assert_equal(p.longest_palindrome_substring('ab', LPS_EXPANSION), 'a')
        assert_equal(p.longest_palindrome_substring('abc', LPS_EXPANSION), 'a')
        assert_equal(p.longest_palindrome_substring('ababa', LPS_EXPANSION), 'ababa')
        assert_equal(p.longest_palindrome_substring('abaaba', LPS_EXPANSION), 'abaaba')
        assert_equal(p.longest_palindrome_substring('abcfgcba', LPS_EXPANSION), 'a')
        assert_equal(p.longest_palindrome_substring(s, LPS_EXPANSION), 'ranynar')
        assert_equal(p.longest_palindrome_substring(r, LPS_EXPANSION), r)

    def test_lps_manacher(self):
        p = Palindrome()
        assert_equal(p.longest_palindrome_substring('', LPS_MANACHER), '')
        assert_equal(p.longest_palindrome_substring('a', LPS_MANACHER), 'a')
        assert_equal(p.longest_palindrome_substring('ab', LPS_MANACHER), 'a')
        assert_equal(p.longest_palindrome_substring('abc', LPS_MANACHER), 'a')
        assert_equal(p.longest_palindrome_substring('ababa', LPS_MANACHER), 'ababa')
        assert_equal(p.longest_palindrome_substring('abaaba', LPS_MANACHER), 'abaaba')
        assert_equal(p.longest_palindrome_substring('abcfgcba', LPS_MANACHER), 'a')
        assert_equal(p.longest_palindrome_substring(s, LPS_MANACHER), 'ranynar')
        assert_equal(p.longest_palindrome_substring(r, LPS_MANACHER), r)
