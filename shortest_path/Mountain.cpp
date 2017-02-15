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
template <typename T> using Matrix = vector<vector<T>>;

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
	 * ���θ� �������� ���� �� �־� ���� ���� �ҿ�Ǵ� ���� ����
	 *
	 * �� ���θ��κ��� �������� ���� ���� ã�� ���� timeover�� ������
	 * ������ ���󿡼� ���θ��� ���� �� ���� ���� ���� �ҿ�Ǵ� ���� ã�ƺ���
	 *
	 * @param start �������� (����� �ִ� ��ǥ����)
	 * @return �ּ� �ҿ� ��
	 */
	auto calcPower(const Point &start) const -> int
	{
		Matrix<int> visited(this->size(), vector<int>(this->size(), INT_MAX));

		return calcPower(start, start, visited, 0);
	};

private:
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
			const Point &prev, const Point &now,
			Matrix<int> &visited, int step
		) const -> int
	{
		// -------------------------------------------
		//	��ó��
		// -------------------------------------------
		if (now.row >= this->size() || now.col >= this->size())
		{
			// ������ ��� -> ������� �ǵ��ư���
			return step + (int)pow(this->at(prev), 2);
		}

		// ������� �Ҹ��� ���� ���
		// ������ �̵��ϱ⿡ ����� �ݴ�� �Ǿ� ��
		if (this->at(now) > this->at(prev))
		{
			// ���������� ���� ���� 
			// (�Ųٷ� �ǵ��ư�, ������ ��������)
			// ���� ���Ǹ�ŭ ���� �ҿ�Ǹ�
			step += this->at(now) - this->at(prev);
		}
		else if (this->at(now) < this->at(prev))
		{
			// ���������� ���� ���� 
			// (�Ųٷ� �ǵ��ư�, ������ ��������)
			// ���� ���� ������ŭ�� ���� �ҿ���
			step += pow(this->at(prev) - this->at(now), 2);
		} 
		// ������ ���� ���� ���� �Ҹ� ����

		// -------------------------------------------
		//	���Ž�� ����
		// -------------------------------------------
		if (visited[now.row][now.col] <= step)
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
				calcPower(now, Point(now.row - 1, now.col), visited, step), // ��
				calcPower(now, Point(now.row + 1, now.col), visited, step), // ��
				calcPower(now, Point(now.row, now.col - 1), visited, step), // ��
				calcPower(now, Point(now.row, now.col + 1), visited, step)  // ��
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