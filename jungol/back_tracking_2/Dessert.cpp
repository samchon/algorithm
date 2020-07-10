#include <iostream>
#include <vector>

#include <algorithm>
#include <cmath>

using namespace std;

/**
 * 중복순열 경우의 수 생성기.
 *
 * 중복순열은 n^r 으로써 0 ~ (n^r - 1) 까지의 숫자를 r 자릿수의 n진수로 나타날 수 있으면 된다.
 */
class CombinedPermutationGenerator
{
private:
	/**
	 * 각 원소가 취할 수 있는 값
	 */
	size_t n;

	/**
	 * 자릿수 R
	 */
	size_t r;

	/**
	 * 경우의 수, n^r개
	 */
	size_t size_;

	/**
	 * 0 ~ (n^r - 1) 까지의 숫자를 각기 i번째의 n진수로 만들어주기 위한 나누기 배열.
	 *
	 * n^i를 담고 있다.
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
	 * index 번째 경우의 수 배열.
	 *
	 * index를 r자리의 n진수로 표현한 것과 같다.
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
		// 경우의 수: {기호 3개 (+, -, .)} ^ (목표 숫자 - 1)
		CombinedPermutationGenerator caseGenerator(3, valueArray.size() - 1);
		vector<size_t> row(valueArray.size() - 1, 0);

		for (size_t i = 0; i < caseGenerator.size(); i++)
		{
			// 각 경우의 수에 대하여
			const vector<size_t> &row = caseGenerator.at(i);

			// 계산하여, 결과가 0이면 추가한다.
			if (calc(row) == 0)
				solutionArray.push_back(row);
		}
	};

	void print()
	{
		for (size_t i = 0; i < min(solutionArray.size(), (size_t)20); i++)
		{
			const vector<size_t> &solution = solutionArray[i];

			// 첫 값을 먼저 출력
			cout << valueArray[0];

			// 기호와 이후 값을 출력
			for (size_t j = 0; j < solution.size(); j++)
			{
				cout << " " << getSign(solution[j]);
				cout << " " << valueArray[j + 1];
			}
			cout << endl;
		}

		// 해답의 개수를 출력
		cout << solutionArray.size();
	};

public:
	/**
	 * 한 수식을 계산함.
	 */
	int calc(const vector<size_t> &row)
	{
		int leftValue = valueArray[0];
		size_t i = 0;

		// . 기호가 있을 때, 좌변을 다시 계산함
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

			// . 기호가 있을 때, 우변을 다시 계산함
			while (j < row.size() && row[j] == DOT)
			{
				int nextValue = valueArray[j + 1];

				// POW를 통해 자릿수를 고려해 새 값을 구하니, 시간이 오래 걸리더라
				//rightValue = rightValue * pow(10, (int)log10(nextValue) + 1) + nextValue;

				// 하드코딩은 시간이 많이 안 걸림
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