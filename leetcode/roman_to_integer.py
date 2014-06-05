"""Key observation: starting from right hand side could reduce some ambiguity."""

from nose.tools import assert_equal

class Solution:
    # @return an integer
    def romanToInt(self, s):
        if not s: return 0
        s = s.upper()
        digits = {'I':1, 'V':5, 'X':10, 'L':50, 'C':100, 'D':500, 'M':1000}
        res = 0
        pos = len(s) - 1
        pre = digits[s[-1]]
        while pos >= 0:
            if digits[s[pos]] >= pre:
                res += digits[s[pos]]
            else:
                res -= digits[s[pos]]
            pre = digits[s[pos]]
            pos -= 1
        return res


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.romanToInt(''), 0)
        assert_equal(s.romanToInt('LVI'), 56)
        assert_equal(s.romanToInt('LIV'), 54)

    def test_example(self):
        s = Solution()
        assert_equal(s.romanToInt('I'), 1)
        assert_equal(s.romanToInt('II'), 2)
        assert_equal(s.romanToInt('III'), 3)
        assert_equal(s.romanToInt('IV'), 4)
        assert_equal(s.romanToInt('V'), 5)
        assert_equal(s.romanToInt('VI'), 6)
        assert_equal(s.romanToInt('VII'), 7)
        assert_equal(s.romanToInt('VIII'),8)
        assert_equal(s.romanToInt('IX'), 9)
        assert_equal(s.romanToInt('X'), 10)
        assert_equal(s.romanToInt('XI'), 11)
        assert_equal(s.romanToInt('XII'), 12)
        assert_equal(s.romanToInt('XIII'), 13)
        assert_equal(s.romanToInt('XIV'), 14)
        assert_equal(s.romanToInt('XV'), 15)
        assert_equal(s.romanToInt('XVI'), 16)
        assert_equal(s.romanToInt('XVII'), 17)
        assert_equal(s.romanToInt('XVIII'), 18)
        assert_equal(s.romanToInt('XIX'), 19)
        assert_equal(s.romanToInt('XX'), 20)
        assert_equal(s.romanToInt('XXI'), 21)
        assert_equal(s.romanToInt('XXII'), 22)
        assert_equal(s.romanToInt('XXIX'), 29)
        assert_equal(s.romanToInt('XXX'), 30)
        assert_equal(s.romanToInt('XXXIV'), 34)
        assert_equal(s.romanToInt('XXXV'), 35 )
        assert_equal(s.romanToInt('XXXIX'), 39)
        assert_equal(s.romanToInt('XL'), 40)
        assert_equal(s.romanToInt('L'), 50)
        assert_equal(s.romanToInt('LI'), 51)
        assert_equal(s.romanToInt('LV'), 55)
        assert_equal(s.romanToInt('LX'), 60)
        assert_equal(s.romanToInt('LXV'), 65)
        assert_equal(s.romanToInt('LXXX'), 80)
        assert_equal(s.romanToInt('XC'), 90)
        assert_equal(s.romanToInt('XCIII'), 93)
        assert_equal(s.romanToInt('XCV'), 95)
        assert_equal(s.romanToInt('XCVIII'), 98)
        assert_equal(s.romanToInt('XCIX'), 99)
        assert_equal(s.romanToInt('C'), 100)
        assert_equal(s.romanToInt('CC'), 200)
        assert_equal(s.romanToInt('CCC'), 300)
        assert_equal(s.romanToInt('CD'), 400)
        assert_equal(s.romanToInt('D'), 500)
        assert_equal(s.romanToInt('DC'),600)
        assert_equal(s.romanToInt('DCC'), 700)
        assert_equal(s.romanToInt('DCCC'), 800)
        assert_equal(s.romanToInt('CM'), 900)
        assert_equal(s.romanToInt('CMXCIX'),999)
        assert_equal(s.romanToInt('M'), 1000)
        assert_equal(s.romanToInt('MC'), 1100)
        assert_equal(s.romanToInt('MCD'), 1400)
        assert_equal(s.romanToInt('MD'), 1500)
        assert_equal(s.romanToInt('MDC'), 1600)
        assert_equal(s.romanToInt('MDCLXVI'), 1666)
        assert_equal(s.romanToInt('MDCCCLXXXVIII'), 1888)
        assert_equal(s.romanToInt('MDCCCXCIX'), 1899)
        assert_equal(s.romanToInt('MCM'), 1900)
        assert_equal(s.romanToInt('MCMLXXVI'), 1976)
        assert_equal(s.romanToInt('MCMLXXXIV'), 1984)
        assert_equal(s.romanToInt('MCMXC'), 1990)
        assert_equal(s.romanToInt('MM'), 2000)
        assert_equal(s.romanToInt('MMMCMXCIX'), 3999)

