#include <iostream>

// https://programmers.co.kr/learn/courses/30/lessons/43238

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

long long solution(int N, vector<int> times) 
{
    int slowest = *max_element(times.begin(), times.end());

    pair<long long, long long> tuple(1, N * (long long)slowest);
    long long ret = (long long)tuple.second;
    
    while (tuple.first <= tuple.second)
    {
        // COMPUTE NUMBER OF THE COMPLETED PEOPLE
        long long mid = (tuple.first + tuple.second) / 2;
        long long completed = 0;

        for (int per : times)
            completed += mid / per;

        // FOR THE NEXT STEP
        if (completed < N)
            tuple.first = mid + 1;
        else
        {
            ret = min(ret, mid);
            tuple.second = mid - 1;
        }
    }
    return ret;
}