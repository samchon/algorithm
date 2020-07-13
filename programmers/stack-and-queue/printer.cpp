// https://programmers.co.kr/learn/courses/30/lessons/42587

#include <vector>
#include <deque>
#include <map>

using namespace std;

int solution(vector<int> priorities, int location) 
{
    // PREPARE ASSETS
    deque<pair<int, size_t>> pairDeque;
    map<int, size_t> countMap;

    for (size_t i = 0; i < priorities.size(); ++i)
    {
        // INSERT
        int value = priorities[i];
        pairDeque.emplace_back(value, i);

        // AAGREGATE
        auto it = countMap.find(value);
        if (it == countMap.end())
            it = countMap.emplace(value, 0).first;
        ++it->second;
    }

    // PRINT ASSETS
    int ret = 0;
    while (pairDeque.empty() == false)
    {
        while (pairDeque.front().first != countMap.rbegin()->first)
        {
            pairDeque.push_back(pairDeque.front());
            pairDeque.pop_front();
        }

        ++ret;
        if (pairDeque.front().second == location)
            break;
        
        auto it = countMap.find(pairDeque.front().first);
        if (--it->second == 0)
            countMap.erase(it);
        pairDeque.pop_front();
    }
    return ret;
}