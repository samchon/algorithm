#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int n, vector<vector<int>> edges) 
{
    size_t connections = edges.size();
    vector<size_t> countList(n + 1, 0);
    
    for (const vector<int> &tuple : edges)
    {
        ++countList[tuple[0]];
        ++countList[tuple[1]];
    }

    int ret = 0;
    for (size_t i = 1; i < countList.size(); ++i)
        if (connections - countList[i] < n)
            ret += i;
    return ret;
}