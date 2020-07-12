// https://programmers.co.kr/learn/courses/30/lessons/42626

#include <vector>
#include <queue>
#include <functional>

using namespace std;

template <class Heap>
int scoville(Heap &heap, int K)
{
    int ret = heap.top();
    heap.pop();

    ret += 2 * heap.top();
    heap.pop();

    return ret;
}

int solution(vector<int> foodList, int K) 
{
    priority_queue<int, vector<int>, greater<int>> heap(foodList.begin(), foodList.end());
    int ret = 0;

    while (heap.top() < K)
    {
        if (heap.size() == 1)
            return -1;
        
        heap.push(scoville(heap, K));
        ++ret;
    }
    return ret;
}