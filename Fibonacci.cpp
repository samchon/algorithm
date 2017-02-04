#include <iostream>
#include <vector>
#include <cmath>

typedef unsigned long long uint64;
using namespace std;

/**
 * 행렬 클래스
 *
 * 피보나치 수열을 구한다.
 * F(x) = power( {(1, 1), (1, 0)}, x )
 */
class Matrix
	: public vector<vector<uint64>>
{
private:
	typedef vector<vector<uint64>> super;

public:
	using super::super;

	/**
	 * 행의 길이
	 */
	auto row() const -> size_t
	{
		return this->size();
	};

	/**
	 * 열의 길이
	 */
	auto col() const -> size_t
	{
		return this->at(0).size();
	};
};

/**
 * 두 행렬을 곱함.
 * 행렬의 각 원소가 10,000 넘을 때, 다시금 10,000의 나머지로 치환한다.
 * 
 * @param left 좌측의 행렬
 * @param right 우측의 행렬
 *
 * @return 두 행렬의 곱
 */
auto operator*(const Matrix &left, const Matrix &right) -> Matrix
{
	Matrix matrix(left.row(), vector<uint64>(right.col(), 0));

	for (size_t r = 0; r < matrix.row(); r++)
		for (size_t c = 0; c < matrix.col(); c++)
		{
			uint64 element = 0;

			for (size_t k = 0; k < left.col(); k++)
			{
				element += left[r][k] * right[k][c];

				// 원소가 10,000 을 넘어서면 나머지로 치환
				if (element >= 10000)
					element = element % 10000;
			}
			matrix[r][c] = element;
		}

	return matrix;
};

/**
 * 행렬의 승수를 구함.
 *
 * @param matrix 행렬
 * @param exponent 승수
 */
auto operator^(const Matrix &matrix, uint64 exponent) -> Matrix
{
	if (exponent == 0)
		return Matrix(matrix.row(), vector<uint64>(matrix.col(), 1));
	else if (exponent == 1)
		return matrix;
	else if (exponent == 2)
		return matrix * matrix;

	// 승수를 반으로 쪼개서 승수를 가한 행렬을 구하고
	Matrix result = matrix ^ (exponent / 2); 
	result = result * result; // 이를 다시 제곱한다

	// 승수가 홀수였다면, 한 번 더 곱함
	if (exponent % 2 == 1)
		result = result * matrix;

	return result;
}

/**
 * 피보나치 수열의 값을 구함
 * 행렬의 곱을 사용
 *
 * @aram x F(x)
 */
auto fibonacci(uint64 x) -> uint64
{
	if (x == 0)
		return 0;
	else if (x == 1)
		return 1;

	Matrix matrix =
	{
		{1, 1},
		{1, 0}
	};
	return (matrix ^ (x - 1))[0][0];
}

int main()
{
	while (true)
	{
		uint64 x;
		cin >> x;

		if (x == -1)
			break;

		cout << fibonacci(x) << endl;
	}

#ifdef _WIN32
	system("pause");
#endif
}