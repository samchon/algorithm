// https://programmers.co.kr/learn/courses/30/lessons/49189?language=cpp

#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

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

vector<Node> create_nodes(const size_t N, const vector<vector<int>> &tupleList)
{
    vector<Node> ret;
    for (size_t i = 0; i <= N; ++i)
        ret.emplace_back(i);

    for (const vector<int>& tuple : tupleList)
    {
        Node &x = ret[tuple[0]];
        Node &y = ret[tuple[1]];

        x.neighbors.push_back(&y);
        y.neighbors.push_back(&x);
    }
    return ret;
}

int solution(int N, vector<vector<int>> edge)
{
    vector<Node> nodeList = create_nodes(N, edge);
    vector<bool> visited(N + 1, false);
    vector<int> distances(N + 1, 0);

    queue<size_t> histories;
    histories.push(1);

    while (histories.empty() == false)
    {
        // PICK ELEMENT
        size_t index = histories.front();
        const Node &from = nodeList.at(index);

        histories.pop();
        for (const Node *node : from.neighbors)
        {
            if (visited.at(node->index) == true)
                continue;

            // FLAG
            histories.push(node->index);
            visited.at(node->index) = true;

            //----
            // SET DISTANCE
            //----
            // NEED NOT TO ADD MINIMUM FILTER,
            // BECAUSE THE SHORTEST PATH WOULD BE INSERTED TO THE BACKWARD
            // CONSIDERING CHARACTERISTICS OF THE QUEUE
            distances.at(node->index) = distances.at(index) + 1;
        }
    }

    // RETURNS
    int greatest = *max_element(distances.begin() + 2, distances.end());
    return count(distances.begin() + 2, distances.end(), greatest);
}