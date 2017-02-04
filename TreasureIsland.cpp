#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define BOOL char

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

/**
 * 좌표 클래스
 */
class Point
{
public:
	size_t row;
	size_t col;

	/**
	 * Construct from 좌표.
	 */
	Point(size_t row, size_t col)
	{
		this->row = row;
		this->col = col;
	};

	auto operator==(const Point &obj) const -> bool
	{
		return row == obj.row && col == obj.col;
	};
	auto operator<(const Point &obj) const -> bool
	{
		if (row != obj.row)
			return row < obj.row;
		else
			return col < obj.col;
	};
};

class Maze
	: public vector<vector<BOOL>>
{
private:
	typedef vector<vector<BOOL>> super;

public:
	/**
	 * Default Constructor.
	 */
	Maze()
		: super()
	{
		// 데이터 입력
		size_t row, col;
		cin >> row >> col;

		assign(row, vector<BOOL>(col, 0));

		for (size_t r = 0; r < row; r++)
		{
			string line;
			cin >> line;

			for (size_t c = 0; c < line.size(); c++)
				at(r).at(c) = (line[c] == 'L');
		}
	};

	using super::at;
	auto at(const Point &p) const -> const BOOL&
	{
		return at(p.row).at(p.col);
	};

	auto row() const -> size_t
	{
		return this->size();
	};
	auto col() const -> size_t
	{
		return this->at(0).size();
	};

	/**
	 * 가장 멀리 있는 지점간의 이동 소요시간을 구함.
	 *
	 * @return 소요시간
	 */
	auto calcHours() -> size_t
	{
		size_t hours = 0;

		for (size_t i = 0; i < row(); i++)
			for (size_t j = 0; j < col(); j++)
			{
				// 존재하는 모든 좌표를 시작지점을 두어 본다
				Point startPoint(i, j);
				if (this->at(startPoint) == false)
					continue;

				// 어떤 시작지점이 가장 멀리 돌아가는가
				size_t myHours = calcHours(startPoint);
				if (myHours != INT_MAX && myHours > hours)
					hours = myHours;
			}

		return hours;
	};

private:
	/**
	 * 각 시작지점 별로, 가장 멀리 있는 지점까지의 이동 소요시간을 구함
	 *
	 * @param startPoint 시작지점
	 * @return 소요시간
	 */
	auto calcHours(const Point &startPoint) -> size_t
	{
		size_t hours = 0;
		vector<vector<size_t>> visitedMatrix(this->row(), vector<size_t>(this->col(), INT_MAX));

		for (size_t i = 0; i < row(); i++)
			for (size_t j = 0; j < col(); j++)
			{
				Point endPoint(i, j);

				if (this->at(endPoint) == false)
					continue;

				size_t myHours = moveTo(startPoint, endPoint, visitedMatrix, 0);
				if (myHours != INT_MAX && myHours > hours)
					hours = myHours;
			}
		return hours;
	};

	/**
	 * 각 지점의 이동간 소요되는 시간을 계산
	 *
	 * @param now 현재 지점
	 * @param endPoint 목표 지점
	 * @param visitedMatrix 각 지점에 방문했을 때 소요된 최소 시간을 담은 행렬
	 * @param step 현재 지점까지 소요한 시간
	 *
	 * @return 총 소요시간
	 */
	auto moveTo
		(
			const Point &now, const Point &endPoint,
			vector<vector<size_t>> &visitedMatrix, size_t step
		) -> size_t
	{
		if (now == endPoint)
		{
			// 목적지까지 도달
			return step;
		}
		else if (now.row >= this->row() || now.col >= this->col())
		{
			// 범위를 벗어남
			return INT_MAX;
		}
		else if (this->at(now) == false)
		{
			// 없는 길로 들어서려 했음
			return INT_MAX;
		}
		else if (step > visitedMatrix[now.row][now.col])
		{
			// 현재 지점을, 더 빨리, 방문한 적이 있다면
			return INT_MAX;
		}

		// 방문지점의 소요시간을 기록한 행렬에, 현재까지 소요한 시간을 기록
		visitedMatrix[now.row][now.col] = step;

		// 최종 소요시간은 상하좌우 중 가장 짧은 시간을 소요하는 것으로 결정됨
		size_t distance =
			min
			({
				moveTo(Point(now.row - 1, now.col), endPoint, visitedMatrix, step + 1),
				moveTo(Point(now.row + 1, now.col), endPoint, visitedMatrix, step + 1),
				moveTo(Point(now.row, now.col - 1), endPoint, visitedMatrix, step + 1),
				moveTo(Point(now.row, now.col + 1), endPoint, visitedMatrix, step + 1)
			});

		return distance;
	};
};

int main()
{
	Maze maze;
	cout << maze.calcHours() << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}