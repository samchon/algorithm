// https://programmers.co.kr/learn/courses/30/lessons/43105

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> triangle)
{
    vector<vector<int>> answers;
    answers.push_back({ triangle[0][0] });

    for (size_t r = 1; r < triangle.size(); ++r)
    {
        vector<int> row;
        for (size_t c = 0; c < r + 1; ++c)
        {
            int value = triangle[r][c];
            if (c == 0)
                value += answers[r-1].front();
            else if (c == r)
                value += answers[r-1].back();
            else
                value += max(answers[r-1][c-1], answers[r-1][c]);

            row.push_back(value);
        }
        answers.push_back(row);
    }

    int best = 0;
    for (int value : answers.back())
        if (value > best)
            best = value;
    return best;
}