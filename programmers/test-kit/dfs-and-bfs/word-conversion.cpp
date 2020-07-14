// https://programmers.co.kr/learn/courses/30/lessons/43163

#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool changeable(const string &x, const string &y)
{
    size_t different = 0;
    for (size_t i = 0; i < x.size(); ++i)
        if (x[i] != y[i])
            ++different;

    return (different == 1);
}

int solve
    (
        const string &current, 
        const string &target, 
        const vector<string> &wordList,
        int step,
        set<string> histories
    )
{
    int ret = 9999;
    histories.insert(current);

    for (const string &word : wordList)
    {
        if (changeable(current, word) == false)
            continue;
        else if (target == word)
            return step;
        else if (histories.count(word) != 0)
            continue;

        int advance = solve(word, target, wordList, step + 1, histories);
        if (advance != 0)
            ret = min(ret, advance);
    }
    return ret;
}

int solution(string begin, string target, vector<string> words) 
{
    if (find(words.begin(), words.end(), target) == words.end())
        return 0;

    return solve(begin, target, words, 1, set<string>());
}