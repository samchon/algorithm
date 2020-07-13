// https://programmers.co.kr/learn/courses/30/lessons/43237

#include <array>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

long long compute(const vector<int> &budgets, const int M, int limit)
{
    long long sum = 0;
    for (int value : budgets)
        sum += min(value, limit);
    return sum;
}

int solution(vector<int> budgets, int M) 
{
    long long sum = compute(budgets, M, M);
    if (sum <= M)
        return *max_element(budgets.begin(), budgets.end());

    pair<int, int> tuple(0, M);

    while (true)
    {
        // COMPUTE THE LIMITED BUDGET
        int mid = (tuple.first + tuple.second) / 2;
        long long y = compute(budgets, M, mid);

        // FOR THE NEXT STEP
        pair<int, int> newTuple = (y > M)
            ? make_pair(tuple.first, mid)
            : make_pair(mid, tuple.second);

        // EXIT OR CONTINUE
        if (tuple == newTuple)
            return mid;
        else
            tuple = newTuple;
    }
}