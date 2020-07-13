// https://programmers.co.kr/learn/courses/30/lessons/42842

#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) 
{
    // brown = 2 * (x + y) - 4
    // yellow = (x - 2) * (y - 2)

    int x_plus_y = (brown + 4) / 2;
    for (int x = x_plus_y - 1; x >= 1; --x)
    {
        int y = x_plus_y - x;
        if ((x-2) * (y - 2) == yellow)
            return { x, y };
    }
}