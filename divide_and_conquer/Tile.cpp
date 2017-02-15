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
	 * Ÿ���� ��ġ��
	 *
	 * ��ġ�� �� �ִ� ��� ����� ���� ����Ͽ�,
	 * ���� ��� ä�� �� �ִ� ���� Ȯ����
	 *
	 * @param prevPoint Ž���� ������ ��ǥ. ������ Ÿ���� �� ��ǥ�̱⵵ ��
	 */
	void cover(const Point &prevPoint)
	{
		Point startPoint(-1, -1);

		// ���� ������ ã�´�
		for (int y = prevPoint.y; y < size(); y++)
		{
			for (int x = (y == prevPoint.y ? prevPoint.x : 0); x < size(); x++)
			{
				// ���� ���� ã�Ƴ� �� ������ ���� ������ �ȴ�.
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
			// ���� ������ ã�Ƴ��� ���ߴ� -> �� ���� ����
			// ���� �� ä������ ������
			success = true;

			return;
		}

		for (int i = 1; i < tileArray.size(); i++)
		{
			if (success == true)
				break;

			if (attach(tileArray[i], startPoint) == false)
				continue;

			// ���� ��ġ�� �ش� Ÿ���� ���� �� �ִٸ�
			// ��� �̾����
			cover(startPoint);

			if (success == false)
			{
				// ���� ��α��� ������ �� �ƴ϶��
				// �ٸ� ����� �� Ž���� ����, ���� Ÿ���� �����
				detach(tileArray[i], startPoint);
			}
		}
	};

	/**
	 * Ÿ���� ������ ��ǥ�� ��ġ�Ѵ�
	 *
	 * @param tile ��ġ�� Ÿ��
	 * @param point Ÿ���� �� ��ǥ
	 *
	 * @return ��ġ ���� ����
	 */
	auto attach(const Tile &tile, const Point &point) -> bool
	{
		const vector<Point> &pointArray = tile.pointArray;

		// ��ȿ�� ����
		for (int i = 0; i < pointArray.size(); i++)
		{
			const Point &myPoint = point + pointArray[i];

			// ������ ����°�
			if (myPoint.x < 0 || myPoint.x >= this->size() || myPoint.y < 0 || myPoint.y >= this->size())
				return false;

			// �ش� ��ǥ�� �� ������ �´°�
			if (this->at(myPoint) != EMPTY)
				return false;
		}

		// Ÿ�� ���̱�
		for (int i = 0; i < pointArray.size(); i++)
		{
			const Point &myPoint = point + pointArray[i];

			this->at(myPoint) = tile.type;
		}
		return true;
	};

	/**
	 * Ư�� ��ġ�� �ִ� Ÿ���� ����
	 *
	 * @param tile ��� Ÿ��
	 * @param point ��� Ÿ���� ��ġ��ǥ
	 */
	void detach(const Tile &tile, const Point &point)
	{
		const vector<Point> &pointArray = tile.pointArray;

		// ��ȿ�� ����
		//for (int i = 0; i < pointArray.size(); i++)
		//{
		//	const Point &myPoint = point + pointArray[i];
		//	
		//	// ������ ����°�
		//	if (myPoint.x < 0 || myPoint.x >= this->size() || myPoint.y < 0 || myPoint.y >= this->size())
		//		return;

		//	// ������� Ÿ���� �ش� ��ġ�� �������� �ʴ´ٸ�
		//	if (this->at(myPoint) != tile.type)
		//		return;
		//}

		// Ÿ���� �����
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