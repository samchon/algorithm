// https://programmers.co.kr/learn/courses/30/lessons/43104

#include <string>
#include <vector>

using namespace std;

long long solution(int N) 
{
    vector<long long> tileList;
    for (size_t i = 0; i < N; ++i)
        if (i < 2)
            tileList.push_back(1);
        else
            tileList.push_back(tileList.back() + *(tileList.rbegin() + 1));

    if (tileList.size() == 1)
        return 4; // 1 * 4
    else if (tileList.size() == 3)
        return 10; // 2*3 + 1*4

    long long *section = &tileList[0] + tileList.size() - 4;
    return section[0]
        + section[1] * 2
        + section[2] * 2
        + section[3] * 3;
}