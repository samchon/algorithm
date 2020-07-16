// https://programmers.co.kr/learn/courses/30/lessons/12974

#include <vector>
#include <array>

using namespace std;

typedef pair<long long, long long> Point;

class Rectangle
{
public:
    const long long x1;
    const long long x2;
    const long long y1;
    const long long y2;

    Rectangle(const vector<int> &tuple)
        : x1(tuple[0]),
          y1(tuple[1]),
          x2(tuple[2]),
          y2(tuple[3])
    {
    };

    long long getArea() const
    {
        return (x2 - x1) * (y2 - y1);
    };

    long long getDuplicatedArea(const Rectangle &obj) const
    {
        long long width = 0;
        long long height = 0;

        // COMPUTE WIDTH
        if (x1 <= obj.x1 && obj.x1 <= x2)
            width = x2 - obj.x1;
        else if (x1 <= obj.x2 && obj.x2 <= x2)
            width = obj.x2 - x1;
        else
            return 0;

        // COMPUTE HEIGHT
        if (y1 <= obj.y1 && obj.y1 <= y2)
            width = y2 - obj.y1;
        else if (y1 <= obj.y2 && obj.y2 <= y2)
            width = obj.y2 - y1;
        else
            return 0;

        // RETURNS
        return width * height;
    };
};

long long solution(vector<vector<int>> tupleList)
{
    vector<Rectangle> rectangles;

    long long sum = 0;
    for (const vector<int> &tuple : tupleList)
    {
        // CREATE A NEW RECTANGLE
        Rectangle rect(tuple);
        sum += rect.getArea();

        // REMOVE DUPLICATES
        for (const Rectangle &obj : rectangles)
            sum -= rect.getDuplicatedArea(obj);
        
        // ENROLL
        rectangles.push_back(rect);
    }
    return sum;
}