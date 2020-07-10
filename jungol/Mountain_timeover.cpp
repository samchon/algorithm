#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define INT_MAX 9999

/**
 * ��ǥ Ŭ����
 */
class Point
{
public:
	/**
	 * ��
	 */
	size_t row;

	/**
	 * ��
	 */
	size_t col;

public:
	/**
	 * Construct from ��ǥ.
	 */
	Point(size_t row, size_t col)
	{
		this->row = row;
		this->col = col;
	};

	/**
	 * �� ��ǥ�� ���� �� ��
	 */
	auto operator==(const Point &obj) const -> bool
	{
		return row == obj.row && col == obj.col;
	};
};

/**
 * ���, �迭�� �迭.
 *
 * @tparam T ���� Ÿ��
 */
template <typename T>
using Matrix = vector<vector<T>>;

/**
 * ���� �� ������ �� ���� �� �̵��� �ҿ�Ǵ� ���� ���� ��� Ŭ����
 *
 * �̵� ���� �ҿ�Ǵ� ���� �줤�ϴ� �Լ� ���� ������ �ִ�.
 */
class Mountain
	: public Matrix<int>
{
private:
	typedef Matrix<int> super;

public:
	/* -----------------------------------------------------
		CONSTRUCTORS
	----------------------------------------------------- */
	/**
	 * Construct from ��������� ũ��.
	 */
	Mountain(size_t size)
		: super(size, vector<int>(size, -1))
	{
		// ������ �Է�
		for (size_t r = 0; r < size; r++)
			for (size_t c = 0; c < size; c++)
				cin >> at(r).at(c);
	};

	/* -----------------------------------------------------
		ACCESSORS
	----------------------------------------------------- */
	using super::at;
	
	auto at(const Point &p) const -> const int&
	{
		return at(p.row).at(p.col);
	};

	/* -----------------------------------------------------
		FINDERS
	----------------------------------------------------- */
	/**
	 * ��ǥ �������� ���� �� �־� ���� ���� �ҿ�Ǵ� ���� ����
	 *
	 * @param end ��ǥ����
	 * @return �ּ� �ҿ� ��
	 */
	auto calcPower(const Point &end) const -> int
	{
		int hours = INT_MAX;

		// ���� �ڸ��� ��ȸ�ؾ� �Ѵ�.
		size_t r, c;
		
		// ��� ������������ ��������
		r = 0;
		for (c = 0; c < this->size(); c++)
			hours = min(hours, calcPower(Point(r, c), end));

		// ���� ������κ��� �ϴܱ���
		c = this->size() - 1;
		for (r = 0; r < this->size(); r++)
			hours = min(hours, calcPower(Point(r, c), end));

		// �ϴ� �������κ��� ��������
		r = this->size() - 1;
		for (c = 0; c < this->size(); c++)
			hours = min(hours, calcPower(Point(r, c), end));

		// ���� �ϴ����κ��� �������
		c = 0;
		for (r = 0; r < this->size(); r++)
			hours = min(hours, calcPower(Point(r, c), end));

		return hours;
	};

private:
	/**
	 * �� ���� �������� ��ǥ �������� ���� �� �־� ���� ���� �ҿ�Ǵ� ���� ����
	 *
	 * @param start ��������
	 * @param end ��ǥ����
	 *
	 * @return �ּ� �ҿ� ��
	 */
	auto calcPower(const Point &start, const Point &end) const -> int
	{
		Point outside(-1, -1);
		Matrix<int> visited(this->size(), vector<int>(this->size(), INT_MAX));

		return calcPower(outside, start, end, visited, 0);
	};

	/**
	 * �� ������ �̵��ÿ� �ҿ�Ǵ� ���� ���
	 *
	 * @param prev ���� ����
	 * @param now ���� ����
	 * @param endP ��ǥ ����
	 * @param visited �� ������ �湮���� �� �ҿ�� �ּ� �ð��� ���� ���
	 * @param step ������� �Ҹ��� �ð�
	 *
	 * @return �ּ� �ҿ� ��
	 */
	auto calcPower
		(
			const Point &prev, const Point &now, const Point &end,
			Matrix<int> &visited, int step
		) const -> int
	{
		// -------------------------------------------
		//	��ó��
		// -------------------------------------------
		if (now.row >= this->size() || now.col >= this->size())
		{
			// ������ ���
			return INT_MAX;
		}

		// ������� �Ҹ��� ���� ���
		if (prev == Point(-1, -1))
		{
			// ù ���
			// ù ������ ���� �����Ѹ�ŭ ���� �Ҹ��Ѵ�
			step = (int)pow(this->at(now), 2);
		}
		else if (this->at(now) > this->at(prev))
		{
			// ���������� ���� ����
			// ���� ���� ������ŭ ���� �ҿ�Ǹ�
			step += (int)pow(this->at(now) - this->at(prev), 2);
		}
		else if (this->at(now) < this->at(prev))
		{
			// ���������� ���� ����
			// ���� �� ��ŭ�� ���� �ҿ���
			step += this->at(prev) - this->at(now);
		} // ������ ���� ���� ���� �Ҹ� ����

		// -------------------------------------------
		//	���Ž�� ����
		// -------------------------------------------
		if (now == end)
		{
			// ��ǥ ������ ������
			return step;
		}
		else if (visited[now.row][now.col] <= step)
		{
			// ���� ������, �� ���� ���� �鿩 �湮�� �� �ִ� ����� �ִ�
			// �� ���� ���� ��η� ��
			return INT_MAX;
		}

		// -------------------------------------------
		//	��� Ž��
		// -------------------------------------------
		// ������ �ҿ�ð��� ��Ŀ� ���
		visited[now.row][now.col] = step;
		
		int power = min
			({
				calcPower(now, Point(now.row - 1, now.col), end, visited, step), // ��
				calcPower(now, Point(now.row + 1, now.col), end, visited, step), // ��
				calcPower(now, Point(now.row, now.col - 1), end, visited, step), // ��
				calcPower(now, Point(now.row, now.col + 1), end, visited, step)  // ��
			});

		return power;
	};
};

int main()
{
/*
5
3 3
1 2 4 3 2
1 3 5 4 4
2 3 6 5 1
3 1 4 1 3
2 3 3 5 3
*/
	size_t size, destRow, destCol;
	cin >> size >> destRow >> destCol;

	Mountain mountain(size);
	cout << mountain.calcPower(Point(destRow - 1, destCol - 1));

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}