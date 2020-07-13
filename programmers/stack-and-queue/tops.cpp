// https://programmers.co.kr/learn/courses/30/lessons/42588

#include <vector>

using namespace std;

vector<int> solution(vector<int> heights) 
{
    vector<int> ret(heights.size(), 0);   

    for (int i = heights.size() - 1; i > 0; --i)
        for (int j = i - 1; j >= 0; --j)
            if (heights[i] < heights[j])
            {
                ret[i] = j + 1;
                break;
            }

    return ret;
}