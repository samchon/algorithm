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
 * 수족관. 
 *
 * 좌표 및 너비 정보를 가지며,
 * 구멍을 뚫고 잔여 너비를 계산하는 메소드를 가진다.
 */
class Aquarium
	: public Point
{
private:
	int width;
	int height;

	/**
	 * 각 가로축 별 세로 길이.
	 */
	map<int, int> heightArray;

	/**
	 * 각 가로축 별 물이 차 있는 세로 너비.
	 */
	map<int, int> areaArray;

public:
	Aquarium()
		: Point(INT_MAX, INT_MAX),
		width(INT_MIN), height(INT_MIN)
	{
		// 좌표 구성
		vector<Point> pointArray;
		size_t size;

		// 좌표를 먼저 다 받아옴
		cin >> size;
		for (size_t i = 0; i < size; i++)
		{
			int x, y;
			cin >> x >> y;

			pointArray.push_back(Point(x, y));

			// 수족관의 좌표와 가로, 세로 길이를 찾아냄
			this->x = min(this->x, x);
			this->y = min(this->y, y);

			this->width = max(this->width, x);
			this->height = max(this->height, y);

			// 각 가로축 별 높이 설정
			if (i % 2 == 1 && i != size - 1)
			{
				// 홀수 index일 때, 높이를 얻을 수 있다.
				// 짝수 -> 세로로 index가 변할 때, y축이 이동하기 때문임
				heightArray[x] = y;
			}
			else if (i != 0)
			{
				// 짝수 index일 때는, 확정된 높이를 확정지어야 한다.
				int prevX = pointArray[i - 1].x;
				int height = heightArray[prevX]; // == y

				for (int newX = prevX + 1; newX < x; newX++)
					heightArray[newX] = height;
			}
		}

		// 가로, 세로 길이 재조정
		this->width -= this->x;
		this->height -= this->y;

		// x + width를 키로 가지는 높이를 제거
		heightArray.erase(x + width);
	};
	
public:
	void punchHole()
	{
		// 물이 차 있는 깊이에, 모든 높이를 복사해 옴
		areaArray = heightArray;

		// 구멍 뚫을 지점을 읽어들임
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

		// 각 구멍으로 인해 빠져나가는 물의 양, 면적을 계산
		for (size_t i = 0; i < holeArray.size(); i++)
		{
			const Point &hole = holeArray[i];

			for (auto it = areaArray.begin(); it != areaArray.end(); it++)
			{
				int x = it->first; // 현재 X 좌표
				int y = heightArray[x]; // 현재 지점의 원래 Y

				int &myHeight = it->second; // 현재 물의 높이
				int myTop = y - myHeight; // 현재 물이 촤오른 윗쪽 지점

				if (hole.x == x)
				{
					// 구멍이 뚫린 바로 그 지점이라면,
					// 물이 다 빠짐
					myHeight = 0;
				}
				else if (myTop < hole.y)
				{
					// 최소 TOP
					int minTop = hole.y;

					// 구멍과 현재 블럭 사이에 더 높은 벽이 있으면 가로막힌다. 그럼 그 벽을 기준으로 다시 구멍을 파야 함
					auto blockIt = heightArray.find(x); // 시작 지점은 현재 블럭
					auto blockEnd = heightArray.find(hole.x); // 끝 지점은 구멍이 위치한 블럭
					int direction = (x < hole.x) ? 1 : -1; // 왼쪽으로 이동할까, 오른쪽으로 이동할까

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