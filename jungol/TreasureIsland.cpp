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
 * ��ǥ Ŭ����
 */
class Point
{
public:
	size_t row;
	size_t col;

	/**
	 * Construct from ��ǥ.
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
		// ������ �Է�
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
	 * ���� �ָ� �ִ� �������� �̵� �ҿ�ð��� ����.
	 *
	 * @return �ҿ�ð�
	 */
	auto calcHours() -> size_t
	{
		size_t hours = 0;

		for (size_t i = 0; i < row(); i++)
			for (size_t j = 0; j < col(); j++)
			{
				// �����ϴ� ��� ��ǥ�� ���������� �ξ� ����
				Point startPoint(i, j);
				if (this->at(startPoint) == false)
					continue;

				// � ���������� ���� �ָ� ���ư��°�
				size_t myHours = calcHours(startPoint);
				if (myHours != INT_MAX && myHours > hours)
					hours = myHours;
			}

		return hours;
	};

private:
	/**
	 * �� �������� ����, ���� �ָ� �ִ� ���������� �̵� �ҿ�ð��� ����
	 *
	 * @param startPoint ��������
	 * @return �ҿ�ð�
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
	 * �� ������ �̵��� �ҿ�Ǵ� �ð��� ���
	 *
	 * @param now ���� ����
	 * @param endPoint ��ǥ ����
	 * @param visitedMatrix �� ������ �湮���� �� �ҿ�� �ּ� �ð��� ���� ���
	 * @param step ���� �������� �ҿ��� �ð�
	 *
	 * @return �� �ҿ�ð�
	 */
	auto moveTo
		(
			const Point &now, const Point &endPoint,
			vector<vector<size_t>> &visitedMatrix, size_t step
		) -> size_t
	{
		if (now == endPoint)
		{
			// ���������� ����
			return step;
		}
		else if (now.row >= this->row() || now.col >= this->col())
		{
			// ������ ���
			return INT_MAX;
		}
		else if (this->at(now) == false)
		{
			// ���� ��� ���� ����
			return INT_MAX;
		}
		else if (step > visitedMatrix[now.row][now.col])
		{
			// ���� ������, �� ����, �湮�� ���� �ִٸ�
			return INT_MAX;
		}

		// �湮������ �ҿ�ð��� ����� ��Ŀ�, ������� �ҿ��� �ð��� ���
		visitedMatrix[now.row][now.col] = step;

		// ���� �ҿ�ð��� �����¿� �� ���� ª�� �ð��� �ҿ��ϴ� ������ ������
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