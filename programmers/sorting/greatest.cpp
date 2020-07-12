// https://programmers.co.kr/learn/courses/30/lessons/42746

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string solution(vector<int> numbers) 
{
    vector<string> words;
    for (auto value : numbers)
        words.push_back(to_string(value));
    sort(words.begin(), words.end(), [](const string &x, const string &y)
    {
        return x + y > y + x;
    });

    if (words.front() == "0")
        return "0";
    
    string ret;
    for (const auto &str : words)
        ret.append(str);

    return ret;
}