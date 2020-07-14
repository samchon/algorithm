// https://programmers.co.kr/learn/courses/30/lessons/42895

#include <vector>
#include <algorithm>

using namespace std;

int solve(int N, int target, int current, int step, int *limit)
{
    if (step >= *limit)
        return *limit;
    else if (current == target)
    {
        *limit = min(step, *limit);
        return step;
    }

    int ret = *limit;
    int next = 0;

    for (int i = 0; i + step < *limit; ++i)
    {
        next = next * 10 + N;
        ret = min
        ({
            *limit,
            solve(N, target, current + next, step + 1 + i, limit),
            solve(N, target, current - next, step + 1 + i, limit),
            solve(N, target, current * next, step + 1 + i, limit),
            solve(N, target, current / next, step + 1 + i, limit)
        });
    }
    return ret;
}

int solution(int N, int target) 
{
    const static int MAX = 9;

    int limit = MAX;
    int ret = solve(N, target, 0, 0, &limit);

    return ret == MAX 
        ? -1 
        : ret;
}