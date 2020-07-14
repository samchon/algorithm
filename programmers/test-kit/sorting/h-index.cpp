// https://programmers.co.kr/learn/courses/30/lessons/42747

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int median(const vector<int> &elements)
{
    double index = elements.size() / 2.0;
    return elements[(size_t)index];
}

int solution(vector<int> citations) 
{
    sort(citations.begin(), citations.end(), greater<int>());

    int ret = 0;
    for (auto value : citations)
        if (value > ret)
            ++ret;
    return ret;
}