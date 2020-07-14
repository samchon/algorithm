#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> left, vector<int> right) 
{
    vector<vector<int>> matrix
    (
        left.size() + 1, 
        vector<int>(right.size() + 1, 0)
    );
    
    for (int i = left.size() - 1; i >= 0; i--)
        for (int j = right.size() - 1; j >= 0; j--)
            if (left[i] > right[j])
                matrix[i][j] = matrix[i][j + 1] + right[j];
            else
                matrix[i][j] = max(matrix[i + 1][j], matrix[i + 1][j + 1]); 
    
    return matrix[0][0];
}