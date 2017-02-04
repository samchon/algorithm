#include <iostream>
#include <vector>
#include <cmath>

typedef unsigned long long uint64;
using namespace std;

/**
 * ��� Ŭ����
 *
 * �Ǻ���ġ ������ ���Ѵ�.
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
	 * ���� ����
	 */
	auto row() const -> size_t
	{
		return this->size();
	};

	/**
	 * ���� ����
	 */
	auto col() const -> size_t
	{
		return this->at(0).size();
	};
};

/**
 * �� ����� ����.
 * ����� �� ���Ұ� 10,000 ���� ��, �ٽñ� 10,000�� �������� ġȯ�Ѵ�.
 * 
 * @param left ������ ���
 * @param right ������ ���
 *
 * @return �� ����� ��
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

				// ���Ұ� 10,000 �� �Ѿ�� �������� ġȯ
				if (element >= 10000)
					element = element % 10000;
			}
			matrix[r][c] = element;
		}

	return matrix;
};

/**
 * ����� �¼��� ����.
 *
 * @param matrix ���
 * @param exponent �¼�
 */
auto operator^(const Matrix &matrix, uint64 exponent) -> Matrix
{
	if (exponent == 0)
		return Matrix(matrix.row(), vector<uint64>(matrix.col(), 1));
	else if (exponent == 1)
		return matrix;
	else if (exponent == 2)
		return matrix * matrix;

	// �¼��� ������ �ɰ��� �¼��� ���� ����� ���ϰ�
	Matrix result = matrix ^ (exponent / 2); 
	result = result * result; // �̸� �ٽ� �����Ѵ�

	// �¼��� Ȧ�����ٸ�, �� �� �� ����
	if (exponent % 2 == 1)
		result = result * matrix;

	return result;
}

/**
 * �Ǻ���ġ ������ ���� ����
 * ����� ���� ���
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