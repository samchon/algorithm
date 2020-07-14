// https://programmers.co.kr/learn/courses/30/lessons/42886

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> weightList) 
{
    sort(weightList.begin(), weightList.end());
    if (weightList.front() > 1)
        return 1;
    
    int ret = 1;
    for (int weight : weightList)
        if (weight > ret + 1)
            break;
        else
            ret += weight;
    return ret;
}