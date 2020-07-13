// https://programmers.co.kr/learn/courses/30/lessons/43165

#include <vector>

using namespace std;

enum Operator
{
    PLUS,
    MINUS
};

int solve(const vector<int> &numbers, const int target, int value, size_t index, Operator op)
{
    // OPERATE
    if (op == Operator::PLUS)
        value += numbers[index];
    else
        value -= numbers[index];
    
    // BREAK
    if (index == numbers.size() - 1)
        return value == target ? 1 : 0;

    // RECURSIVE CALL
    return solve(numbers, target, value, index + 1, Operator::PLUS)
        + solve(numbers, target, value, index + 1, Operator::MINUS);
}

int solution(vector<int> numbers, int target) 
{
    return solve(numbers, target, 0, 0, Operator::PLUS)
        + solve(numbers, target, 0, 0, Operator::MINUS);
}