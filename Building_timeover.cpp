#include <iostream>
#include <vector>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

/**
 * ���, �迭�� �迭.
 *
 * @tparam T ���� Ÿ��
 */
template <typename T> using Matrix = vector<vector<T>>;

/**
 * ����� �� �� N! ������
 */
class FactorialGenerator
{
private:
	/**
	 * �� ���Ұ� ���� �� �ִ� ���� ������ �ڸ� ��
	 */
	size_t n;

	/**
	 * ������ ��� ����� �� ����.
	 */
	size_t size_;

	/**
	 * 1 ~ n���� ��Ƶ� ���� �迭. 
	 * ������ ���� ���� �迭�̴�.
	 */
	vector<size_t> atomArray;

public:
	FactorialGenerator(size_t n)
	{
		this->n = n;

		size_ = n;
		for (size_t i = n - 1; i >= 1; i--)
			size_ *= i;

		atomArray.assign(n, 0);
		for (size_t i = 0; i < n; i++)
			atomArray[i] = i;
	};

	auto size() const -> size_t
	{
		return size_;
	};

	/**
	 * Index��° ����� ���� �޾ƿ´�.
	 */
	auto at(size_t index) const -> vector<size_t>
	{
		// �ϴ� 0 ~ n-1 ���� ��ȣ�� ��� ���� �迭�� �����
		vector<size_t> atomArray = this->atomArray;
		vector<size_t> row(n, 0);

		for (size_t i = 0; i < n; i++)
		{
			size_t item = index % atomArray.size(); // index�� ���� ������ �������� �޾ƿ�
			row[i] = atomArray[item]; // �� ��ȣ��� ����� ���� Ȯ����

			index = index / atomArray.size(); // ���� ������ ���� index�� ����
			atomArray.erase(atomArray.begin() + item); // ���� ����� ��ȣ item�� ����
		}

		return row;
	};
};

auto calcCost(const Matrix<int> &matrix, const vector<size_t> &row) -> int
{
	int sum = 0;
	for (size_t i = 0; i < row.size(); i++)
	{
		// i��° �ǹ��� row[i]��° ������ �ǹ��� �ø�
		sum += matrix[i][row[i]];
	}
	return sum;
}
void print(int cost, const vector<size_t> row)
{
	cout << cost << endl;
	for (size_t i = 0; i < row.size(); i++)
		cout << (row[i] + 1) << " ";
}

int main()
{
/*
4
11 12 18 40
14 15 13 22
11 17 19 23
17 14 20 28
*/

	Matrix<int> matrix;
	size_t size;

	cin >> size;
	matrix.assign(size, vector<int>(size, 0));

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			cin >> matrix[i][j];

	FactorialGenerator factorial(size);
	int minCost = INT_MAX;
	size_t minIndex = 0;

	for (size_t i = 0; i < factorial.size(); i++)
	{
		const vector<size_t> &row = factorial.at(i);
		int myCost = calcCost(matrix, row);

		if (myCost < minCost)
		{
			minCost = myCost;
			minIndex = i;
		}
	}

	print(minCost, factorial.at(minIndex));

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}