// https://programmers.co.kr/learn/courses/30/lessons/49189?language=cpp

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAX = 999999999;

class Node
{
public:
    size_t index;
    vector<const Node*> neighbors;

    Node(size_t index)
    {
        this->index = index;
    };
};

int compute(const Node* from, const Node* to, int moved, vector<bool>& visited, int &champion)
{
    if (from == to)
    {
        champion = min(champion, moved);
        return moved;
    }
    else if (moved >= champion)
        return MAX;

    visited[from->index] = true;
    int ret = MAX;

    for (const Node* node : from->neighbors)
    {
        if (visited[node->index] == true)
            continue;

        ret = min(ret, compute(node, to, moved + 1, visited, champion));
    }

    visited[from->index] = false;
    return ret;
}

int compute(int n, const Node* from, const Node* to)
{
    vector<bool> visited(n + 1, false);
    int champion = MAX;

    return compute(from, to, 0, visited, champion);
}

int solution(int n, vector<vector<int>> edge)
{
    vector<Node> nodeList;
    for (size_t i = 1; i <= n; ++i)
        nodeList.emplace_back(i);

    for (const vector<int>& tuple : edge)
    {
        Node* x = &nodeList[tuple[0] - 1];
        Node* y = &nodeList[tuple[1] - 1];

        x->neighbors.push_back(y);
        y->neighbors.push_back(x);
    }

    map<int, int> distanceMap;
    for (auto it = nodeList.begin() + 1; it != nodeList.end(); ++it)
    {
        int distance = compute(n, &nodeList.front(), &*it);
        if (distance == MAX)
            continue;
        
        ++distanceMap.emplace(distance, 0).first->second;
    }
    return distanceMap.rbegin()->second;
}