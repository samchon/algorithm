#include <iostream>
using namespace std;

class Board
{
public:
	long long width;
	long long height;

	Board(long long width, long long height)
	{
		this->width = width;
		this->height = height;
	};
};

class Ant
{
public:
	Board *board;

	long long x;
	long long y;
	long long directionX;
	long long directionY;

	Ant(Board *board, long long x, long long y)
	{
		this->board = board;
		this->x = x;
		this->y = y;

		this->directionX = 1;
		this->directionY = 1;
	};

	void move()
	{
		if (x + directionX < 0 || x + directionX > board->width)
			this->directionX *= -1;
		
		if (y + directionY < 0 || y + directionY > board->height)
			this->directionY *= -1;

		this->x += directionX;
		this->y += directionY;
	};
	void print()
	{
		cout << x << " " << y << endl;
	};
};

int main()
{
	long long boardX, boardY;
	long long antX, antY;
	long long movement;

	cin >> boardX >> boardY;
	cin >> antX >> antY;
	cin >> movement;

	Board board(boardX, boardY);
	Ant ant(&board, antX, antY);

	for (long long i = 0; i < movement; i++)
		ant.move();

	ant.print();
	return 0;
}