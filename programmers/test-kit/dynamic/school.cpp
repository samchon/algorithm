#include <vector>

using namespace std;

int solution(int m, int n, vector<vector<int>> puddles) 
{
    // PREPARE MATRIX
    vector<vector<int>> matrix(n, vector<int>(m, 1));

    // DIG PUDDLES
    for (const vector<int> &tuple : puddles)
    {
        size_t r = tuple[1] - 1;
        size_t c = tuple[0] - 1;
        matrix[r][c] = 0;

        // WHEN EDGE POSITION, CLOSE THE SIDE ALL
        if (r == 0)
            for (size_t i = c + 1; i < m; ++i)
                matrix[r][i] = 0;
        else if (c == 0)
            for (size_t i = r + 1; i < n; ++i)
                matrix[i][c] = 0;
    }

    // FIND ROUTINES
    for (size_t r = 1; r < n; ++r)
        for (size_t c = 1; c < m; ++c)
        {
            int *location = &matrix[r][c];
            if (*location == 0)
                continue; // SKIP PUDDLE

            int x = matrix[r-1][c];
            int y = matrix[r][c-1];

            *location = (x + y) % 1000000007;
        }
    return matrix[n-1][m-1];
}