// https://programmers.co.kr/learn/courses/30/lessons/42841

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<int> predicate(string value, string knock)
{
    vector<int> ret(2, 0);
    unordered_set<char> characters(value.begin(), value.end());

    for (size_t i = 0; i < knock.size(); ++i)
    {
        char ch = knock[i];
        if (ch == value[i])
            ++ret[0];
        else if (characters.count(ch) == 1)
            ++ret[1];
    }
    return ret;
}

int solution(vector<vector<int>> gameList) 
{
    int ret = 0;

    for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j)
    for (int k = 1; k <= 9; ++k)
    {
        if (i == j || j == k || k == i)
            continue;

        string value = to_string(i) + to_string(j) + to_string(k);
        size_t match = 0;

        for (const auto &tuple : gameList)
        {
            string knock = to_string(tuple[0]);
            vector<int> answer = predicate(value, knock);

            if (answer[0] == tuple[1] && answer[1] == tuple[2])
                ++match;
        }
        if (match == gameList.size())
            ++ret;
    }
    return ret;
}