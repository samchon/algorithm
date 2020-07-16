#include <vector>
#include <algorithm>

using namespace std;

class Core
{
private:
    const int time;
    int current;


public:
    Core(int time) : time(time) 
    {
        this->current = 0;
    };

    bool empty() const
    {
        return current == 0;
    };

    void assign()
    {
        this->current = time;
    };

    bool process()
    {
        return --current;
    };

    int left() const
    {
        return current;
    };
};

int solution(int n, vector<int> timeList) 
{
    vector<Core> coreList;
    for (int time : timeList)
        coreList.emplace_back(time);

    bool completed = false;
    while (completed == false)
        for (size_t i = 0; i < coreList.size(); ++i)
        {
            Core &core = coreList[i];
            if (n >= 0 && core.empty())
            {
                core.assign();
                if (--n == 0)
                    completed = true;
            }
            if (!core.empty())
                core.process();
        }

    auto it = max_element(coreList.begin(), coreList.end(), [](const Core &x, const Core &y) { return x.left() < y.left(); });
    return it - coreList.begin();
};