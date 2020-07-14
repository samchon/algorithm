#include <vector>
#include <set>
#include <utility>

using namespace std;

typedef pair<int, int> Point;
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int solution(vector<int> arrows) 
{
    set<Point> pointHistories;
    set<pair<Point, Point>> passHistories;

    // START FROM THE ZERO POINT
    Point prev(0, 0);
    pointHistories.insert(prev);

    int ret = 0;
    for(int symbol : arrows)
        for(int j = 0; j < 2; j++)
        {
            // MOVE POINT
            Point point = prev;
            point.first += dx[symbol];
            point.second += dy[symbol];

            // ARCHIVE HISTORIES
            bool newbie = pointHistories.insert(point).second;
            pair<bool, bool> newRoutine = {
                passHistories.emplace(prev, point).second,
                passHistories.emplace(point, prev).second
            };

            // THE POINT MET A WITH DIFFICULT ANGLED EDGE ?
            if (newbie == false && (newRoutine.first || newRoutine.second))
                ++ret;

            // FOR THE NEXT STEP
            prev = point;
        }
    return ret;
}