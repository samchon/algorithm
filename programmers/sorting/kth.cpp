// https://programmers.co.kr/learn/courses/30/lessons/42748

#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) 
{
    vector<int> ret;

    for (auto &tuple : commands)
    {
        vector<int> elements(array.begin() + tuple[0] - 1, array.begin() + tuple[1]);
        sort(elements.begin(), elements.end());

        ret.push_back(elements[tuple[2] - 1]);
    }
    return ret;
}