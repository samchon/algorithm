#include <iostream>
#include <vector>
#include <set>
#include <array>

#define EMPTY -1
#define HOLL 0

using namespace std;

class Point
{
public:
	int x;
	int y;

	Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	};

	auto operator+(const Point &p) const -> Point
	{
		return Point(x + p.x, y + p.y);
	};
};

class Tile
{
public:
	int type;
	vector<Point> pointArray;

	Tile()
	{
		this->type = 0;
	};
	Tile(int type)
	{
		this->type = type;
		
		if (type == 1)
			pointArray = { Point(0, 0), Point(0, 1), Point(-1, 1) };
		else if (type == 2)
			pointArray = { Point(0, 0), Point(0, 1), Point(1, 1) };
		else if (type == 3)
			pointArray = { Point(0, 0), Point(1, 0), Point(1, 1) };
		else if (type == 4)
			pointArray = { Point(0, 0), Point(0, 1), Point(1, 0) };
	};
};

class Board
	: public vector<vector<int>>
{
private:
	typedef vector<vector<int>> super;

	vector<Tile> tileArray;
	bool success;

public:
	Board(int size)
		: super(size, vector<int>(size, EMPTY))
	{
		for (int i = 0; i <= 4; i++)
			tileArray.push_back(Tile(i));

		success = false;
	};

	using super::at;
	auto at(const Point &p) -> int&
	{
		return at(p.y).at(p.x);
	};

	void cover()
	{
		cover(Point(0, 0));
	};

	void print()
	{
		for (int y = 0; y < size(); y++)
		{
			for (int x = 0; x < size(); x++)
				cout << at(Point(x, y)) << " ";
			cout << endl;
		}
	};

private:
	/**
	 * 타일을 배치함
	 *
	 * 배치할 수 있는 모든 경우의 수를 고려하여,
	 * 판을 모두 채울 수 있는 경우로 확정함
	 *
	 * @param prevPoint 탐색을 시작할 좌표. 이전에 타일이 깔린 좌표이기도 함
	 */
	void cover(const Point &prevPoint)
	{
		Point startPoint(-1, -1);

		// 시작 지점을 찾는다
		for (int y = prevPoint.y; y < size(); y++)
		{
			for (int x = (y == prevPoint.y ? prevPoint.x : 0); x < size(); x++)
			{
				// 가장 먼저 찾아낸 빈 지점이 시작 지점이 된다.
				Point myPoint(x, y);
				if (this->at(myPoint) == EMPTY)
				{
					startPoint = myPoint;
					break; // DOUBLE BREAK
				}
			}
			if (startPoint.y != -1) // DOUBLE BREAK
				break;
		}

		if (startPoint.y == -1)
		{
			// 시작 지점을 찾아내지 못했다 -> 빈 곳이 없다
			// 전부 다 채웠으니 성공임
			success = true;

			return;
		}

		for (int i = 1; i < tileArray.size(); i++)
		{
			if (success == true)
				break;

			if (attach(tileArray[i], startPoint) == false)
				continue;

			// 현재 위치에 해당 타일을 붙일 수 있다면
			// 계속 이어나간다
			cover(startPoint);

			if (success == false)
			{
				// 최종 경로까지 도달한 게 아니라면
				// 다른 경우의 수 탐색을 위해, 현재 타일을 떼어낸다
				detach(tileArray[i], startPoint);
			}
		}
	};

	/**
	 * 타일을 지정된 좌표에 배치한다
	 *
	 * @param tile 배치할 타일
	 * @param point 타일을 깔 좌표
	 *
	 * @return 배치 성공 여부
	 */
	auto attach(const Tile &tile, const Point &point) -> bool
	{
		const vector<Point> &pointArray = tile.pointArray;

		// 유효성 검증
		for (int i = 0; i < pointArray.size(); i++)
		{
			const Point &myPoint = point + pointArray[i];

			// 범위를 벗어났는가
			if (myPoint.x < 0 || myPoint.x >= this->size() || myPoint.y < 0 || myPoint.y >= this->size())
				return false;

			// 해당 좌표가 빈 공간이 맞는가
			if (this->at(myPoint) != EMPTY)
				return false;
		}

		// 타일 붙이기
		for (int i = 0; i < pointArray.size(); i++)
		{
			const Point &myPoint = point + pointArray[i];

			this->at(myPoint) = tile.type;
		}
		return true;
	};

	/**
	 * 특정 위치에 있는 타일을 뗀다
	 *
	 * @param tile 떼어낼 타일
	 * @param point 떼어낼 타일의 위치좌표
	 */
	void detach(const Tile &tile, const Point &point)
	{
		const vector<Point> &pointArray = tile.pointArray;

		// 유효성 검증
		//for (int i = 0; i < pointArray.size(); i++)
		//{
		//	const Point &myPoint = point + pointArray[i];
		//	
		//	// 범위를 벗어났는가
		//	if (myPoint.x < 0 || myPoint.x >= this->size() || myPoint.y < 0 || myPoint.y >= this->size())
		//		return;

		//	// 떼어내려는 타일이 해당 위치에 존재하지 않는다면
		//	if (this->at(myPoint) != tile.type)
		//		return;
		//}

		// 타일을 떼어낸다
		for (int i = 0; i < pointArray.size(); i++)
		{
			const Point &myPoint = point + pointArray[i];

			this->at(myPoint) = EMPTY;
		}
	};
};

int main()
{
	int size;
	Point hole;

	cin >> size >> hole.y >> hole.x;

	Board board(size);
	board.at(hole) = HOLL;

	board.cover();
	board.print();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}