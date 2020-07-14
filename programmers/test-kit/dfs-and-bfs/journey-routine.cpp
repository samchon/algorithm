// https://programmers.co.kr/learn/courses/30/lessons/43164

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void travel(const vector<vector<string>> &tickets, const string &from, vector<string> &histories, vector<bool> &used)
{
    histories.push_back(from);
    if (histories.size() == tickets.size() + 1)
        return;

    for (size_t i = 0; i < tickets.size(); ++i)
    {
        const vector<string> &routine = tickets[i];
        if (routine[0] != from || used[i] == true)
            continue;

        used[i] = true;

        travel(tickets, routine[1], histories, used);
        if (histories.size() == tickets.size() + 1)
            return;

        used[i] = false;
    }
    histories.pop_back();
}

vector<string> solution(vector<vector<string>> tickets) 
{
    // SORT TICKETS FIRST
    sort(tickets.begin(), tickets.end());

    // TRAVEL LATER
    vector<string> histories;
    vector<bool> used(tickets.size(), false);

    travel(tickets, "ICN", histories, used);
    return histories;
}