// https://www.acmicpc.net/problem/13460

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int LIMIT = 10;
enum Direction { UP, DOWN, LEFT, RIGHT };

class Marble
{
public:
    char color;
    int row;
    int col;

    Marble(char color, int row, int col)
    {
        this->color = color;
        this->row = row;
        this->col = col;
    };

    void move(int row, int col)
    {
        this->row = row;
        this->col = col;
    };
};

int explore(const vector<vector<char>>& map, const vector<Marble>& marbles, int step);
int explore(const vector<vector<char>>& map, vector<Marble> marbleList, Direction direction, int step);

int explore(const vector<vector<char>>& map, vector<Marble> marbleList, Direction direction, int step)
{
    static const int RY[] = { -1, 1, 0, 0 };
    static const int RX[] = { 0, 0, -1, 1 };

    // SORT BY DIRECTION
    sort(marbleList.begin(), marbleList.end(), 
        [direction](const Marble &x, const Marble &y)
        {
            if (direction == Direction::UP)
                return x.row < y.row;
            else if (direction == Direction::LEFT)
                return x.col < y.col;
            else if (direction == Direction::RIGHT)
                return x.col > y.col;
            else
                return x.row > y.row;
        });

    // MOVE ALL MARBLES
    for (size_t i = 0; i < marbleList.size(); ++i)
    {
        Marble& marble = marbleList[i];

        while (true)
        {
            int r = marble.row + RY[(size_t)direction];
            int c = marble.col + RX[(size_t)direction];

            // OUT-OF-RANGE
            if (r < 0 || r >= map.size())
                break;
            else if (c < 0 || c >= map[0].size())
                break;
            else if (map[r][c] == '#')
                break;

            // DROP INTO THE HALL
            if (map[r][c] == 'o')
                if (marble.color == 'R')
                    return step;
                else
                    return LIMIT + 1;

            // BLOCKED BY ANOTHER MARBLE
            bool blocked = false;
            for (size_t j = 0; j < marbleList.size(); ++j)
                if (i != j)
                {
                    Marble& obj = marbleList[j];
                    if (r == obj.row && c == obj.col)
                    {
                        blocked = true;
                        break;
                    }
                }
            if (blocked == true)
                break;

            // SUCCEEDED TO MOVE
            marble.move(r, c);
        }
    }

    // NO RETURN, THEN EXPLORE MORE
    return explore(map, marbleList, step + 1);
}

int explore(const vector<vector<char>>& map, const vector<Marble>& marbles, int step)
{
    // TERMINATE THE LOOP
    if (step > LIMIT)
        return LIMIT + 1;

    return min({
        explore(map, marbles, Direction::UP, step),
        explore(map, marbles, Direction::DOWN, step),
        explore(map, marbles, Direction::LEFT, step),
        explore(map, marbles, Direction::RIGHT, step)
    });
}

int main()
{
    size_t height, width;
    cin >> height >> width;

    vector<vector<char>> map(height, vector<char>(width, ' '));
    vector<Marble> marbles;

    for (size_t r = 0; r < height; ++r)
        for (size_t c = 0; c < width; ++c)
        {
            char ch;
            cin >> ch;

            if (ch == 'R' || ch == 'B')
            {
                marbles.emplace_back(ch, (int)r, (int)c);
                map[r][c] = '.';
            }
            else
                map[r][c] = ch;
        }

    int ret = explore(map, marbles, 1);
    if (ret == LIMIT + 1)
        ret = -1;

    cout << ret;
    return 0;
}