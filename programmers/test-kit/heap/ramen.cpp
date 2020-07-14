// https://programmers.co.kr/learn/courses/30/lessons/42629

#include <vector>
#include <queue>

using namespace std;

int solution(int stock, vector<int> dates, vector<int> supplies, int k) 
{
    priority_queue<int> heap;
    int ret = 0;
    int index = 0;

    for (int i = 0; i < k; ++i)
    {
        if (dates[index] == i)
        {
            heap.push(supplies[index]);
            ++index;
        }

        if (stock == 0)
        {
            stock = heap.top();
            heap.pop();

            ++ret;
        }
        --stock;
    }
    return ret;
}