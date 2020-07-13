// https://programmers.co.kr/learn/courses/30/lessons/42862

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) 
{
    // LIST UP CURRENT STATUS
    vector<int> participants(n, 1);
    for (int index : lost)
        participants[index - 1] = 0;
    for (int index : reserve)
        ++participants[index - 1];

    // BORROW FROM NEIGHBORS
    for (size_t i = 0; i < participants.size(); ++i)
    {
        // NEED NOT TO BORRW
        int value = participants[i];
        if (value != 0)
            continue;

        if (i != 0 && participants[i-1] > 1)
        {
            // BORROW FROM LEFT
            --participants[i-1];
            ++participants[i];
        }
        else if (i != participants.size() - 1 && participants[i+1] > 1)
        {
            // BORROW FROM RIGHT
            --participants[i+1];
            ++participants[i];
        }
    }

    return participants.size() - count(participants.begin(), participants.end(), 0);
}