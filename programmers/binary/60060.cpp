// https://programmers.co.kr/learn/courses/30/lessons/60060

#include <iostream>
#include <vector>
#include <map>

#include <algorithm>
#include <iterator>
#include <utility>

using namespace std;

pair<string, bool> decompose_query(const string& query)
{
    string ret;
    copy_if(query.begin(), query.end(), back_inserter(ret), [](char x) 
    { 
        return x != '?';
    });

    bool reversed = (query[0] == '?');
    if (reversed == true)
        ret = string(ret.rbegin(), ret.rend()); 

    return make_pair(ret, reversed);
}

int count_query(const vector<string>& wordList, const string& prefix)
{
    // prefix + zzzzz~
    string after = prefix;
    for (size_t i = 0; i < wordList[0].size() - prefix.size(); ++i)
        after.push_back('z');

    // first in the range
    auto first = lower_bound(wordList.begin(), wordList.end(), prefix);
    if (first == wordList.end() || first->substr(0, prefix.size()) != prefix)
        return 0;
    
    // next of the last in the range
    auto next_of_the_last = upper_bound(wordList.begin(), wordList.end(), after);
    return next_of_the_last - first;
}

vector<int> solution(vector<string> wordList, vector<string> queries)
{
    //----
    // PREPARE ASSETS
    //----
    // construct dictionary
    //   - key: size
    //   - value: pair of words right and reverse ordered
    map<size_t, pair<vector<string>, vector<string>>> dictionary;

    for (auto word : wordList)
    {
        auto it = dictionary.find(word.size());
        if (it == dictionary.end())
        {
            // no size yet, then make new pair
            it = dictionary.emplace(word.size(), make_pair(vector<string>(), vector<string>())).first;
            it->second.first.reserve(word.size());
            it->second.second.reserve(word.size());
        }

        // insert the word
        it->second.first.push_back(word);
        it->second.second.emplace_back(word.rbegin(), word.rend());
    }

    // Sort items
    for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
    {
        sort(it->second.first.begin(), it->second.first.end());
        sort(it->second.second.begin(), it->second.second.end());
    }

    //----
    // COUNT QUERIES
    //----
    vector<int> ret;
    ret.reserve(queries.size());

    for (auto query : queries)
    {
        // target sized words exist ?
        auto it = dictionary.find(query.size());
        if (it == dictionary.end())
        {
            ret.push_back(0);
            continue;
        }

        // decompose query and select target words
        pair<string, bool> decomposed = decompose_query(query);
        vector<string>& target_words = decomposed.second
            ? it->second.second
            : it->second.first;

        // count the query
        ret.push_back( count_query(target_words, decomposed.first) );
    }
    return ret;
}

int main()
{
    vector<int> ret = solution
    (
        { "frodo", "front", "frost", "frozen", "frame", "kakao" },
        { "fro??", "????o", "fr???", "fro???", "pro?" }
    );

    for (auto elem : ret)
        cout << elem << endl;

    return 0;
}