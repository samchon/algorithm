// https://programmers.co.kr/learn/courses/30/lessons/42586

#include <vector>
#include <map>
#include <cmath>

using namespace std;

vector<int> solution(vector<int> progressList, vector<int> speedList)
{
    map<int, size_t> dayCounts;
    
    for (size_t i = 0; i < progressList.size(); ++i)
    {
        int progress = progressList[i];
        int speed = speedList[i];
        int days = (int)ceil((100.0 - progress) / (double)speed);

        if (i != 0 && dayCounts.rbegin()->first > days)
            days = dayCounts.rbegin()->first;

        auto it = dayCounts.find(days);
        if (it == dayCounts.end())
            it = dayCounts.emplace(days, 0).first;
        ++it->second;
    }

    vector<int> ret;
    for (auto &it : dayCounts)
        ret.push_back(it.second);
    return ret;
}