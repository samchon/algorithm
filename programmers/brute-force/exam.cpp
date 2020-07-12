// https://programmers.co.kr/learn/courses/30/lessons/42840

#include <vector>
#include <algorithm>

using namespace std;

inline int A(size_t index)
{
    return index % 5 + 1;
}

inline int B(size_t index)
{
    const static int SOLUTIONS[] = { 1, 3, 4, 5 };
    return index % 2 == 0
        ? 2
        : SOLUTIONS[(size_t)(index / 2) % 4];
}

inline int C(size_t index)
{
    const static int SOLUTIONS[] = { 3, 1, 2, 4, 5 };
    return SOLUTIONS[(size_t)(index / 2) % 5];
}

vector<int> solution(vector<int> answerList)
{
    vector<int> scores(3, 0);
    for (size_t i = 0; i < answerList.size(); ++i)
    {
        int value = answerList[i];

        if (A(i) == value)
            ++scores[0];
        if (B(i) == value)
            ++scores[1];
        if (C(i) == value)
            ++scores[2];
    }
    
    vector<int> ret;
    int highest = max(scores[0], max(scores[1], scores[2]));

    for (size_t i = 0; i < scores.size(); ++i)
        if (scores[i] == highest)
            ret.push_back(i + 1);
    return ret;
}