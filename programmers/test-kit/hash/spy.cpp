// https://programmers.co.kr/learn/courses/30/lessons/42578

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) 
{
    unordered_map<string, int> typeCounts;
    for (auto &pair : clothes)
    {
        const string &type = pair[1];
        auto it = typeCounts.find(type);

        if (it == typeCounts.end())
            it = typeCounts.emplace(type, 0).first;
        ++it->second;
    }

    int ret = 1;
    for (auto &it : typeCounts)
        ret *= it.second + 1; // 입지 않는 경우: + 1
    return ret - 1; // 아무 것도 입지 않는 경우: -1
}