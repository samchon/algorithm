// https://programmers.co.kr/learn/courses/30/lessons/49191

#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> results) 
{
    vector<vector<bool>> winMatrix(n + 1, vector<bool>(n + 1, false));
    for (const vector<int> &tuple : results)
        winMatrix[tuple[0]][tuple[1]] = true;

    for (size_t i = 1; i <= n; ++i)
    for (size_t j = 1; j <= n; ++j)
    for (size_t k = 1; k <= n; ++k)
        if (winMatrix[j][i] == true && winMatrix[i][k] == true)
            winMatrix[j][k] = true;

    int ret = 0;
    for (size_t i = 1; i <= n; ++i)
    {
        int count = 0;
        for (size_t j = 1; j <= n; ++j)
            if (winMatrix[i][j] == true || winMatrix[j][i] == true)
                ++count;
        if (count == n - 1)
            ++ret;
    }
    return ret;
}