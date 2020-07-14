// https://programmers.co.kr/learn/courses/30/lessons/42899

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void assign
    (
        const int K,
        const pair<int, int> &mobile, 
        vector<vector<int>> &dp, 
        size_t i, size_t j
    )
{
    size_t weight = j + mobile.first;
    if (weight > K)
        return;

    int prev = dp[i-1][j];
    int &next = dp[i][weight];

    next = max(next, prev + mobile.second);
}

int solution(int K, vector<vector<int>> travel) 
{
    // PREPARE DP
    vector<vector<int>> dp
    (
        travel.size(),
        vector<int>(K + 1, 0)
    );

    for (size_t i = 0; i < travel.size(); ++i)
    {
        const vector<int> &tuple = travel[i];
        pair<int, int> walk(tuple[0], tuple[1]);
        pair<int, int> bike(tuple[2], tuple[3]);

        if (i == 0)
        {
            // INITIALIZE DP
            dp[0][walk.first] = walk.second;
            dp[0][bike.first] = bike.second;

            continue;
        }

        // ITERATE ALL THE WEIGHTS
        for (size_t j = 0; j <= K; ++j)
        {
            if (dp[i-1][j] == 0)
                continue;
            
            assign(K, walk, dp, i, j);
            assign(K, bike, dp, i, j);
        }
    }

    int ret = 0;
    for (int value : dp.back())
        if (value > ret)
            ret = value;
    return ret;
}