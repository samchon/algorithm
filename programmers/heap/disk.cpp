// https://programmers.co.kr/learn/courses/30/lessons/42627

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Comparator
{
    bool operator()(const vector<int> *x, const vector<int> *y) const
    {
        return x->at(1) > y->at(1);
    };
};

int solution(vector<vector<int>> jobList)
{
    // SORT JOB REQUESTS
    sort(jobList.begin(), jobList.end(), 
        [](const vector<int> &x, const vector<int> &y)
        {
            return x[0] < y[0];
        });

    // PREPARE ASSETS
    priority_queue<vector<int>*, vector<vector<int>*>, Comparator> heap;
    int time = 0;
    int index = 0;

    int ret = 0;
    while (index < jobList.size() || heap.empty() == false)
    {
        if (index < jobList.size() && time >= jobList[index][0])
            heap.push(&jobList[index++]); // NEW PROCESS
        else if (heap.empty() == true)
            time = jobList[index][0]; // STEP TO THE NEXT TIME
        else
        {
            // FINISH PROCESS
            time += heap.top()->at(1);
            ret += time - heap.top()->at(0);

            heap.pop();
        }
    }

    // RETURNS AVERAGE TIME
    return ret / jobList.size();
}