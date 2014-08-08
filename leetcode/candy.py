from nose.tools import assert_equal

class Solution:
    # @param ratings, a list of integer
    # @return an integer
    def candy(self, ratings):
        #return self._solve_naive(ratings)
        #return self._solve_2pass(ratings)
        return self._solve_1pass(ratings)

    def _solve_naive(self, ratings):
        order = zip(ratings, range(len(ratings)))
        order = [ o[1] for o in sorted(order) ]
        candies = [ 0 ] * len(ratings)
        for o in order:
            if candies[o] == 0:
                candies[o] = 1
                idx = o - 1
                while idx >= 0 and ratings[idx] > ratings[idx+1]:
                    if candies[idx] != 0:
                        if candies[idx] < candies[idx+1] + 1:
                            candies[idx] = candies[idx+1] + 1
                        break
                    candies[idx] = candies[idx+1] + 1
                    idx -= 1
                idx = o + 1
                while idx < len(ratings) and ratings[idx] > ratings[idx-1]:
                    if candies[idx] != 0:
                        if candies[idx] < candies[idx-1] + 1:
                            candies[idx] = candies[idx-1] + 1
                        break
                    candies[idx] = candies[idx-1] + 1
                    idx += 1
        return sum(candies)

    def _solve_2pass(self, ratings):
        candies = [ 1 ] * len(ratings)
        for i in range(1, len(ratings)):
            if ratings[i] > ratings[i-1]:
                candies[i] = candies[i-1] + 1
        #print candies
        for i in range(len(ratings)-1)[::-1]:
            if ratings[i] > ratings[i+1]:
                candies[i] = max(candies[i+1] + 1, candies[i])
        #print candies
        return sum(candies)

    def _solve_1pass(self, ratings):
        """
        https://oj.leetcode.com/discuss/76/does-anyone-have-a-better-idea
        """
        down_seq_len = 0
        total = ratings and 1 or 0
        prev = 1
        prev_max = prev
        for i in range(1, len(ratings)):
            if ratings[i] < ratings[i-1]:
                down_seq_len += 1
                if prev_max == down_seq_len:
                    down_seq_len += 1
                total += down_seq_len
                prev = 1
            else:
                if ratings[i] > ratings[i-1]:
                    prev += 1
                else:
                    prev = 1
                total += prev
                down_seq_len = 0
                prev_max = prev
        return total


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        assert_equal(s.candy([]), 0)

    def test_example(self):
        s = Solution()
        #assert_equal(s.candy([1,2,2]), 4)
        assert_equal(s.candy([4,2,3,4,1]), 9)
