// https://programmers.co.kr/learn/courses/30/lessons/42897

#include <vector>
#include <algorithm>

using namespace std;

int steal(const vector<int> &moneyList, vector<int> seed, size_t limit)
{
    for (size_t i = 2; i < limit; ++i)
    {
        // STREAL OR HOLD
        int value = max(seed[i - 2] + moneyList[i], seed[i - 1]);
        seed.push_back(value);
    }   
    return seed.back();
}

int solution(vector<int> moneyList) 
{
    return max(
        steal(moneyList, { moneyList[0], moneyList[0] }, moneyList.size() - 1),
        steal(moneyList, { 0, moneyList[1] }, moneyList.size())
    );
}