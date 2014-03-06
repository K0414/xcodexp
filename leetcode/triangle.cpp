#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        vector<int> sum;
        sum = triangle.back();
        for (int i = triangle.size() - 1; i > 0; i--)
        {
            vector<int> &row = triangle[i-1];
            for ( int j = 0; j < i; j++)
            {
                sum[j] = min(sum[j], sum[j+1]) + row[j];
            }
        }
        return sum[0];
    }
};

int main()
{
    Solution sol;
    vector<vector<int> > triangle;
    int row1[] = {2};
    int row2[] = {3,4};
    int row3[] = {6,5,7};
    int row4[] = {4,1,8,3};
    vector<int> vec1(row1, row1 + sizeof(row1) / sizeof(int));
    vector<int> vec2(row2, row2 + sizeof(row2) / sizeof(int));
    vector<int> vec3(row3, row3 + sizeof(row3) / sizeof(int));
    vector<int> vec4(row4, row4 + sizeof(row4) / sizeof(int));
    triangle.push_back(vec1);
    triangle.push_back(vec2);
    triangle.push_back(vec3);
    triangle.push_back(vec4);
    cout << sol.minimumTotal(triangle) << endl;
    return 0;
}
