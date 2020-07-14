// https://programmers.co.kr/learn/courses/30/lessons/42584

#include <vector>

using namespace std;

vector<int> solution(vector<int> priceList)
{
    vector<int> ret(priceList.size(), 0);
    for (size_t i = 0; i < priceList.size() - 1; ++i)
    {
        int myPrice = priceList[i];

        for (size_t j = i + 1; j < priceList.size(); ++j)
        {
            ++ret[i];
            if (myPrice > priceList[j])
                break;
        }
    }
    return ret;
}