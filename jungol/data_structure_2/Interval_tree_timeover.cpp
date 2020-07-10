#include <iostream>
#include <vector>

#include <algorithm>
#include <cmath>
#include <memory>

#define INT_MIN -1

using namespace std;

class Interval
{
private:
	unique_ptr<Interval> left;
	unique_ptr<Interval> right;

	size_t begin;
	size_t end;
	int value;

public:
	Interval(size_t begin, size_t end)
	{
		this->begin = begin;
		this->end = end;
		this->value = INT_MIN;

		if (end - begin != 1)
		{
			size_t mid = (begin + end) / 2;

			left.reset(new Interval(begin, mid));
			right.reset(new Interval(mid, end));
		}
		else
		{
			left = nullptr;
			right = nullptr;
		}
	};

	void setValue(size_t index, int val)
	{
		if (left == nullptr)
			this->value = val;
		else
		{
			if (index < (begin + end) / 2)
				left->setValue(index, val);
			else
				right->setValue(index, val);

			this->value = max(left->value, right->value);
		}
	};

	auto getValue(size_t begin, size_t end) const -> int
	{
		if (this->begin > end || this->end < begin)
			return INT_MIN; // 아예 다른 범위이다.
		else if (begin <= this->begin && this->end <= end)
			return this->value; // 현재 범위를 포함한다.
		else
		{
			if (left == nullptr)
				return INT_MIN;
			else
				return max(left->getValue(begin, end), right->getValue(begin, end));
		}
	};
};

class IntervalTree
	: public vector<int>
{
private:
	typedef vector<int> super;

	unique_ptr<Interval> root;
	size_t height;

public:
	IntervalTree(size_t size)
	{
		super::assign(size, 0);
		root.reset(new Interval(0, size));

		height = log2(size);
	};

	void setValue(size_t index, int val)
	{
		at(index) = val;
		root->setValue(index, val);
	};

	auto getValue(size_t begin, size_t end) const -> int
	{
		if (end - begin < height)
		{
			int maxValue = at(begin);
			for (size_t i = begin + 1; i < end; i++)
				maxValue = max(maxValue, at(i));

			return maxValue;
		}
		else
			return root->getValue(begin, end);
	};
};

int main()
{
	/////////////////////////////////////////////////////
	// 데이터 구성
	/////////////////////////////////////////////////////
	size_t valueSize;
	size_t intervalSize;

	cin >> valueSize >> intervalSize;

	IntervalTree tree(valueSize);
	vector<pair<size_t, size_t>> intervalArray(intervalSize);

	// 각 원소 입력
	for (size_t i = 0; i < valueSize; i++)
	{
		int value;
		cin >> value;

		tree.setValue(i, value);
	}

	/////////////////////////////////////////////////////
	// 각 구간별 최대값 계산 & 출력
	/////////////////////////////////////////////////////
	for (size_t i = 0; i < intervalSize; i++)
	{
		size_t begin;
		size_t end;

		cin >> begin >> end;
		cout << tree.getValue(begin - 1, end) << endl;
	}

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}