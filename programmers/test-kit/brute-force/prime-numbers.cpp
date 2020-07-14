// https://programmers.co.kr/learn/courses/30/lessons/42839

#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool isPrime(long long value)
{
    if (value < 2)
        return false;
    
    for (long long i = 2; i <= sqrt(value); ++i)
        if (value % i == 0)
            return false;
    return true;
}

int solution(string numbers) 
{
    sort(numbers.begin(), numbers.end());

    set<int> ret;
    do
    {
        for (size_t i = 1; i <= numbers.size(); ++i)
        {
            long long value = stoll(numbers.substr(0, i));
            if (isPrime(value) == true)
                ret.insert(value);
        }
    }
    while (next_permutation(numbers.begin(), numbers.end()));

    return ret.size();
}