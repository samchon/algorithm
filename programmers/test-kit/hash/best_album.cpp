// https://programmers.co.kr/learn/courses/30/lessons/42579

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Aggregate
{
public:
    size_t count;
    vector<pair<int, size_t>> plays;

    Aggregate()
    {
        this->count = 0;
    }
};

vector<int> solution(vector<string> genres, vector<int> playList) 
{
    // AGGREGATE THROUGH DICTIONARY
    unordered_map<string, Aggregate> dict;
    for (size_t i = 0; i < genres.size(); ++i)
    {
        const string &gen = genres[i];
        int play = playList[i];

        auto it = dict.find(gen);
        if (it == dict.end())
            it = dict.emplace(gen, Aggregate()).first;
        
        it->second.count += play;
        it->second.plays.push_back(make_pair(play, i));
    }

    // LINEARLIZE THEM
    vector<Aggregate*> aggregateList;
    for (auto &it : dict)
        aggregateList.push_back(&it.second);

    // SORT AGGREGATES USING COUNT
    sort(aggregateList.begin(), aggregateList.end(), 
        [](Aggregate *x, Aggregate *y)
        {
            return x->count > y->count;
        });

    // PICK SONGS
    vector<int> ret;
    for (auto agg : aggregateList)
    {
        if (ret.size() >= 4)
            break;

        sort(agg->plays.begin(), agg->plays.end(), 
            [](pair<int, size_t> &x, pair<int, size_t> &y)
            {
                return x.first != y.first
                    ? x.first > y.first
                    : x.second < y.second;
            });

        for (size_t j = 0; (j < agg->plays.size() && j < 2 && ret.size() < 4); ++j)
            ret.push_back(agg->plays[j].second);
    }
    return ret;
}