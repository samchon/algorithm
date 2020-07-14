// https://programmers.co.kr/learn/courses/30/lessons/42862

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string name) 
{
    size_t horizontal = name.size() - 1;
    size_t vertical = 0;

    for (size_t i = 0; i < name.size(); ++i)
    {
        // BASIC COUNTING
        vertical += min(name[i] - 'A', 'Z' - name[i] + 1);

        // STEP TO THE RIGHT
        size_t move = 1;
        while ((i + move) < name.size() && name[i + move] == 'A') 
            ++move;

        // FIND THE SHORTEST MOVEMENT
        horizontal = min(horizontal, name.size() - move + i);
    }
    return horizontal + vertical;
}