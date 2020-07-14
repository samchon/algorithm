#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> routes) 
{
    sort(routes.begin(), routes.end(), 
        [](const vector<int> &x, const vector<int> &y)
        {
            return x[0] < y[0];
        });
    
    int ret = 1;
    int last = routes.front()[1];

    for (auto movement : routes)
        if (last < movement[0])
        {
            // OUT OF RANGE
            last = movement[1];
            ++ret;
        }
        else
            last = min(last, movement[1]);

    return ret;
}