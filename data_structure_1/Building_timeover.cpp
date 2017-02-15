#include <iostream>
#include <vector>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

/**
 * 행렬, 배열의 배열.
 *
 * @tparam T 원소 타입
 */
template <typename T> using Matrix = vector<vector<T>>;

/**
 * 경우의 수 中 N! 생성기
 */
class FactorialGenerator
{
private:
	/**
	 * 각 원소가 취할 수 있는 값의 수이자 자릿 수
	 */
	size_t n;

	/**
	 * 가능한 모든 경우의 수 개수.
	 */
	size_t size_;

	/**
	 * 1 ~ n까지 담아둔 원소 배열. 
	 * 복제를 위한 샘플 배열이다.
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
	 * Index번째 경우의 수를 받아온다.
	 */
	auto at(size_t index) const -> vector<size_t>
	{
		// 일단 0 ~ n-1 까지 번호가 담긴 원소 배열을 만들고
		vector<size_t> atomArray = this->atomArray;
		vector<size_t> row(n, 0);

		for (size_t i = 0; i < n; i++)
		{
			size_t item = index % atomArray.size(); // index와 원소 갯수의 나머지를 받아와
			row[i] = atomArray[item]; // 그 번호대로 경우의 수를 확정함

			index = index / atomArray.size(); // 다음 과정을 위해 index를 조정
			atomArray.erase(atomArray.begin() + item); // 현재 사용한 번호 item도 없앰
		}

		return row;
	};
};

auto calcCost(const Matrix<int> &matrix, const vector<size_t> &row) -> int
{
	int sum = 0;
	for (size_t i = 0; i < row.size(); i++)
	{
		// i번째 건물이 row[i]번째 부지에 건물을 올림
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