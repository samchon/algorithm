// https://programmers.co.kr/learn/courses/30/lessons/42576?language=cpp

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> participants, vector<string> completions) 
{
    sort(participants.begin(), participants.end());
    sort(completions.begin(), completions.end());

    auto it = mismatch(completions.begin(), completions.end(), participants.begin());
    return *(it.second);
}