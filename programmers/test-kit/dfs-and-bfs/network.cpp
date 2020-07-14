// https://programmers.co.kr/learn/courses/30/lessons/43162

#include <vector>
#include <set>

using namespace std;

size_t find(const vector<size_t> &topNodes, size_t node)
{
    return (node == topNodes[node])
        ? node
        : find(topNodes, topNodes[node]);
}

int solution(int n, vector<vector<int>> computers) 
{
    vector<size_t> topNodes;
    for (size_t i = 0; i < n; ++i)
        topNodes.push_back(i);

    for (const vector<int> &tuple : computers)
    {
        vector<size_t> nodeList;
        size_t minimum = tuple.size();

        for (size_t i = 0; i < n; ++i)
            if (tuple[i] == 1)
            {
                size_t node = find(topNodes, i);
                if (node < minimum)
                    minimum = node;
                nodeList.push_back(node);
            }

        for (size_t node : nodeList)
            topNodes[node] = minimum;
    }

    set<size_t> nodeSet;
    for (size_t i = 0; i < n; ++i)
        nodeSet.insert(find(topNodes, i));
    return nodeSet.size();
}