// https://programmers.co.kr/learn/courses/30/lessons/42628

#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(vector<string> operations) 
{
    multiset<int> elements;

    for (const string &command : operations)
    {
        char type = command[0];
        int value = stoi(command.substr(2));

        if (type == 'I')
            elements.insert(value);
        else if (type == 'D')
        {
            if (elements.empty() == true)
                continue;
            else if (value == 1)
                elements.erase(--elements.end());
            else
                elements.erase(elements.begin());
        }
    }

    return elements.empty()
        ? vector<int>({ 0, 0 })
        : vector<int>({ *elements.rbegin(), *elements.begin() });
}