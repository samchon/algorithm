// https://programmers.co.kr/learn/courses/30/lessons/42577

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool solution(vector<string> numberList) 
{
    sort(numberList.begin(), numberList.end());
    
    bool prefix = false;
    for (size_t i = 0; i < numberList.size() - 1; ++i)
    {
        const string &x = numberList[i];
        const string &y = numberList[i+1];

        if (y.size() >= x.size() && y.substr(0, x.size()) == x)
        {
            prefix = true;
            break;
        }
    }
    return !prefix;
}