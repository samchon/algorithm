// https://programmers.co.kr/learn/courses/30/lessons/1839

#include <vector>
#include <utility>

using namespace std;

typedef pair<long long, long long> Tuple;

vector<int> solution(int height, int width, int limit, vector<vector<int>> timeMap) 
{
    static const long long MAX = (long long)((unsigned int)-1) + 1;

    vector<vector<Tuple>> dp(height, vector<Tuple>(width, { 0, 0 }));
    const Tuple dummy(-1, -1 * timeMap[0][0]);

    for (size_t r = 0; r < height; ++r)
    for (size_t c = 0; c < width; ++c)
    {
        // SELECT NEIGHBOR
        const Tuple &top = (r != 0) ? dp[r-1][c] : dummy;
        const Tuple &left = (c != 0) ? dp[r][c-1] : dummy;
        const Tuple &from 
            = (r == 0) ? left
            : (c == 0) ? top
            : (top.second < left.second) ? top : left;

        // SELECT TIME
        long long time = timeMap[r][c];
        if (time == -1 || from.second + time >= limit)
            time = MAX;
        else
            time = from.second + time;
        
        dp[r][c] = { from.first + 1, time };
    }

    const Tuple &last = dp.back().back();
    return vector<int>({ (int)last.first, (int)last.second });
}