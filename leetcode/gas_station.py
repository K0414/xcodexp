from nose.tools import assert_equal

class Solution:
    # @param gas, a list of integers
    # @param cost, a list of integers
    # @return an integer
    def canCompleteCircuit(self, gas, cost):
        if not gas or not cost: return 0
        gas = gas
        cost = cost
        net = [ gas[i] - cost[i] for i in range(len(gas)) ]
        net *= 2
        n = len(net)
        s = 0
        c = 0
        i = 0
        while i < n:
            s += net[i]
            c += 1
            if s < 0:
                # Key observation:
                # Each previous component from start is none-negative,
                # removing any one won't lead to a increase for the sum,
                # just restart counting from next position.
                s = 0
                c = 0
            if c == n/2:
                return i - c + 1
            i += 1
        return -1


class TestSolution(object):

    def test_simple(self):
        s = Solution()
        gas = [1,2,3,4,5,6,7]
        cost = [1,2,3,4,5,6,7]
        assert_equal(s.canCompleteCircuit(gas, cost), 0)
        gas = [1,2,3,4,5,6,7]
        cost = [1,2,4,4,5,6,7]
        assert_equal(s.canCompleteCircuit(gas, cost), -1)
        gas = [1,2,3,4,5,7,7]
        cost = [1,2,4,4,5,6,7]
        assert_equal(s.canCompleteCircuit(gas, cost), 3)

    def test_example(self):
        s = Solution()
        gas = [4]
        cost = [5]
        assert_equal(s.canCompleteCircuit(gas, cost), -1)
