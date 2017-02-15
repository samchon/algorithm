#include <iostream>
#include <vector>

#include <algorithm>
#include <cmath>

using namespace std;

/**
 * �ߺ����� ����� �� ������.
 *
 * �ߺ������� n^r ���ν� 0 ~ (n^r - 1) ������ ���ڸ� r �ڸ����� n������ ��Ÿ�� �� ������ �ȴ�.
 */
class CombinedPermutationGenerator
{
private:
	/**
	 * �� ���Ұ� ���� �� �ִ� ��
	 */
	size_t n;

	/**
	 * �ڸ��� R
	 */
	size_t r;

	/**
	 * ����� ��, n^r��
	 */
	size_t size_;

	/**
	 * 0 ~ (n^r - 1) ������ ���ڸ� ���� i��°�� n������ ������ֱ� ���� ������ �迭.
	 *
	 * n^i�� ��� �ִ�.
	 */
	vector<size_t> dividerArray;

public:
	CombinedPermutationGenerator(size_t n, size_t r)
	{
		this->n = n;
		this->r = r;

		this->size_ = pow(n, r);
		this->dividerArray.assign(r, 0);

		for (size_t i = 0; i < r; i++)
		{
			size_t x = r - (i + 1);
			dividerArray[i] = (size_t)pow(n, x);
		}
	};

	size_t size() const
	{
		return size_;
	}

	/**
	 * index ��° ����� �� �迭.
	 *
	 * index�� r�ڸ��� n������ ǥ���� �Ͱ� ����.
	 */
	vector<size_t> at(size_t index) const
	{
		vector<size_t> row(r, 0);

		for (size_t i = 0; i < row.size(); i++)
			row[i] = (index / dividerArray[i]) % n;

		return row;
	};
};

class Dessert
{
public:
	static const size_t PLUS = 0;
	static const size_t MINUS = 1;
	static const size_t DOT = 2;

	vector<int> valueArray;
	vector<vector<size_t>> solutionArray;

public:
	Dessert(size_t size)
	{
		for (int i = 1; i <= size; i++)
			valueArray.push_back(i);
	};

	void retrieve()
	{
		// ����� ��: {��ȣ 3�� (+, -, .)} ^ (��ǥ ���� - 1)
		CombinedPermutationGenerator caseGenerator(3, valueArray.size() - 1);
		vector<size_t> row(valueArray.size() - 1, 0);

		for (size_t i = 0; i < caseGenerator.size(); i++)
		{
			// �� ����� ���� ���Ͽ�
			const vector<size_t> &row = caseGenerator.at(i);

			// ����Ͽ�, ����� 0�̸� �߰��Ѵ�.
			if (calc(row) == 0)
				solutionArray.push_back(row);
		}
	};

	void print()
	{
		for (size_t i = 0; i < min(solutionArray.size(), (size_t)20); i++)
		{
			const vector<size_t> &solution = solutionArray[i];

			// ù ���� ���� ���
			cout << valueArray[0];

			// ��ȣ�� ���� ���� ���
			for (size_t j = 0; j < solution.size(); j++)
			{
				cout << " " << getSign(solution[j]);
				cout << " " << valueArray[j + 1];
			}
			cout << endl;
		}

		// �ش��� ������ ���
		cout << solutionArray.size();
	};

public:
	/**
	 * �� ������ �����.
	 */
	int calc(const vector<size_t> &row)
	{
		int leftValue = valueArray[0];
		size_t i = 0;

		// . ��ȣ�� ���� ��, �º��� �ٽ� �����
		while (i < row.size() && row[i] == DOT)
		{
			int myValue = valueArray[i + 1];
			leftValue = leftValue * pow(10.0, (int)log10(myValue) + 1) + myValue;

			i++;
		}

		while (i < row.size())
		{
			int rightValue = valueArray[i + 1];
			size_t j = i + 1;

			// . ��ȣ�� ���� ��, �캯�� �ٽ� �����
			while (j < row.size() && row[j] == DOT)
			{
				int nextValue = valueArray[j + 1];

				// POW�� ���� �ڸ����� ����� �� ���� ���ϴ�, �ð��� ���� �ɸ�����
				//rightValue = rightValue * pow(10, (int)log10(nextValue) + 1) + nextValue;

				// �ϵ��ڵ��� �ð��� ���� �� �ɸ�
				if (nextValue < 10)
					rightValue = rightValue * 10 + nextValue;
				else
					rightValue = rightValue * 100 + nextValue;

				j++;
			}

			if (row[i] == PLUS)
				leftValue += rightValue;
			else
				leftValue -= rightValue;

			i = j;
		}

		return leftValue;
	};
	char getSign(size_t sign)
	{
		if (sign == PLUS)
			return '+';
		else if (sign == MINUS)
			return '-';
		else
			return '.';
	}
};

int main()
{
	size_t size;
	cin >> size;

	Dessert dessert(size);
	dessert.retrieve();
	dessert.print();

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}