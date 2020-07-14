// https://programmers.co.kr/learn/courses/30/lessons/42883

#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) 
{
    string ret;
    int length = number.size() - k;

    for (char ch : number)
    {
        // ERASE SMALLER DIGITS THAN CURRENT
        while (k > 0 && ret.empty() == false && ret.back() < ch)
        {
            --k;
            ret.pop_back();
        }
        ret.push_back(ch);
    }

    // PARTIAL RETURN
    return ret.substr(0, length);
}