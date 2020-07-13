// https://programmers.co.kr/learn/courses/30/lessons/42885

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) 
{
    sort(people.begin(), people.end());

    int ret = 0;
    int i = 0; 
    int j = people.size() - 1; 
    
    while (i < j + 1) 
    {
        if (people[i] + people[j] <= limit)
            ++i;
        --j;
        ++ret;
    }
    
    return ret;
}