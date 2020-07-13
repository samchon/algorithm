// https://programmers.co.kr/learn/courses/30/lessons/42585

#include <string>
#include <vector>
#include <set>
#include <stack>

using namespace std;

int solution(string arrangement)
{
    stack<size_t> startPositions;
    vector<pair<size_t, size_t>> barList;
    set<size_t> laserSet;

    // CONSTRUCT BARS AND LASER POINTS
    for (size_t i = 0; i < arrangement.size(); ++i)
    {
        char ch = arrangement[i];
        if (ch == '(')
            startPositions.push(i);
        else if (ch == ')')
        {
            size_t start = startPositions.top();
            startPositions.pop();

            if (i - start == 1)
                laserSet.insert(i);
            else
                barList.emplace_back(start, i);
        }
    }

    // CUT THEM ALL
    int ret = barList.size();
    for (const auto &bar : barList)
        for (auto it = laserSet.upper_bound(bar.first); it != laserSet.end(); ++it)
            if (bar.second > *it)
                ++ret;
    
    return ret;
}