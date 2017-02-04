#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#ifndef INT_MAX
#	define INT_MAX (-1U)/2
#	define INT_MIN (INT_MAX+1)
#endif

using namespace std;

class Point
{
public:
	int x;
	int y;

	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	};
};

/**
 * ������. 
 *
 * ��ǥ �� �ʺ� ������ ������,
 * ������ �հ� �ܿ� �ʺ� ����ϴ� �޼ҵ带 ������.
 */
class Aquarium
	: public Point
{
private:
	int width;
	int height;

	/**
	 * �� ������ �� ���� ����.
	 */
	map<int, int> heightArray;

	/**
	 * �� ������ �� ���� �� �ִ� ���� �ʺ�.
	 */
	map<int, int> areaArray;

public:
	Aquarium()
		: Point(INT_MAX, INT_MAX),
		width(INT_MIN), height(INT_MIN)
	{
		// ��ǥ ����
		vector<Point> pointArray;
		size_t size;

		// ��ǥ�� ���� �� �޾ƿ�
		cin >> size;
		for (size_t i = 0; i < size; i++)
		{
			int x, y;
			cin >> x >> y;

			pointArray.push_back(Point(x, y));

			// �������� ��ǥ�� ����, ���� ���̸� ã�Ƴ�
			this->x = min(this->x, x);
			this->y = min(this->y, y);

			this->width = max(this->width, x);
			this->height = max(this->height, y);

			// �� ������ �� ���� ����
			if (i % 2 == 1 && i != size - 1)
			{
				// Ȧ�� index�� ��, ���̸� ���� �� �ִ�.
				// ¦�� -> ���η� index�� ���� ��, y���� �̵��ϱ� ������
				heightArray[x] = y;
			}
			else if (i != 0)
			{
				// ¦�� index�� ����, Ȯ���� ���̸� Ȯ������� �Ѵ�.
				int prevX = pointArray[i - 1].x;
				int height = heightArray[prevX]; // == y

				for (int newX = prevX + 1; newX < x; newX++)
					heightArray[newX] = height;
			}
		}

		// ����, ���� ���� ������
		this->width -= this->x;
		this->height -= this->y;

		// x + width�� Ű�� ������ ���̸� ����
		heightArray.erase(x + width);
	};
	
public:
	void punchHole()
	{
		// ���� �� �ִ� ���̿�, ��� ���̸� ������ ��
		areaArray = heightArray;

		// ���� ���� ������ �о����
		vector<Point> holeArray;
		size_t size;
		cin >> size;

		for (size_t i = 0; i < size; i++)
		{
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;

			for (int x = x1; x < x2; x++)
				holeArray.push_back(Point(x, y1));
		}

		// �� �������� ���� ���������� ���� ��, ������ ���
		for (size_t i = 0; i < holeArray.size(); i++)
		{
			const Point &hole = holeArray[i];

			for (auto it = areaArray.begin(); it != areaArray.end(); it++)
			{
				int x = it->first; // ���� X ��ǥ
				int y = heightArray[x]; // ���� ������ ���� Y

				int &myHeight = it->second; // ���� ���� ����
				int myTop = y - myHeight; // ���� ���� �ҿ��� ���� ����

				if (hole.x == x)
				{
					// ������ �ո� �ٷ� �� �����̶��,
					// ���� �� ����
					myHeight = 0;
				}
				else if (myTop < hole.y)
				{
					// �ּ� TOP
					int minTop = hole.y;

					// ���۰� ���� �� ���̿� �� ���� ���� ������ ���θ�����. �׷� �� ���� �������� �ٽ� ������ �ľ� ��
					auto blockIt = heightArray.find(x); // ���� ������ ���� ��
					auto blockEnd = heightArray.find(hole.x); // �� ������ ������ ��ġ�� ��
					int direction = (x < hole.x) ? 1 : -1; // �������� �̵��ұ�, ���������� �̵��ұ�

					for (; blockIt != blockEnd; advance(blockIt, direction))
						minTop = min(minTop, blockIt->second);

					myHeight = min(myHeight, max(0, y - minTop));
				}
			}
		}
	};

	int getArea() const
	{
		int area = 0;
		for (auto it = areaArray.begin(); it != areaArray.end(); it++)
			area += it->second;

		return area;
	};
};

int main()
{
	Aquarium aquarium;
	aquarium.punchHole();

	cout << aquarium.getArea();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}