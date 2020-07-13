#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int find(const vector<int> &topNodes, int node)
{
    return (node == topNodes[node])
        ? node
        : find(topNodes, topNodes[node]);
}

int solution(int n, vector<vector<int>> tupleList) 
{
    // INITIALIZE PARENT NODES
    vector<int> topNodes;
    for (int i = 0; i < n; ++i)
        topNodes.push_back(i);

    // SORT TUPLES BY COST
    sort(tupleList.begin(), tupleList.end(), 
        [](const vector<int> &x, const vector<int> &y)
        {
            return x[2] < y[2];
        });

    int ret = 0;
    for (const vector<int> &tuple : tupleList)
    {
        // FIND ROUTINE
        int x = find(topNodes, tuple[0]);
        int y = find(topNodes, tuple[1]);
        int cost = tuple[2];

        if (x != y)
        {
            // THE NEW ROUTINE
            topNodes[x] = y;
            ret += cost;
        }
    }
    return ret;
}