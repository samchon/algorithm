#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Interval
{
public:
	static vector<int> elementArray;
	static const Interval *lastInterval;

	size_t start;
	size_t end;

	size_t maxIndex;
	
	Interval(size_t start, size_t end)
	{
		this->start = start;
		this->end = end;

		this->maxIndex = -1;
	};

	void calcMax()
	{
		int maxValue;

		if (lastInterval == nullptr || lastInterval->maxIndex < start || lastInterval->maxIndex >= end)
		{
			// ó�� ���ϴ� MAX ���̰ų�, 
			// Ȥ�� ���� �ִ밪 index�� ������ ������ ����� ���̶��
			// FULL SCAN�� �Ѵ�
			maxValue = -1;

			for (size_t i = start; i < end; i++)
				if (elementArray[i] > maxValue)
				{
					maxValue = elementArray[i];
					maxIndex = i;
				}
		}
		else
		{
			// ������ ���س��� MAX ���� �ְ�, �� MAX�� index�� ���� ���� ������ �ִٸ�,
			// �̸� ���� PARTIAL SCANNING �� �����Ѵ�.
			maxValue = lastInterval->getMaxValue();
			maxIndex = lastInterval->maxIndex;
			
			for (size_t i = lastInterval->end; i < end; i++)
				if (elementArray[i] > maxValue)
				{
					maxValue = elementArray[i];
					maxIndex = i;
				}
		}
		lastInterval = this;
	};

	auto getMaxValue() const -> int
	{
		return elementArray[maxIndex];
	};
};
vector<int> Interval::elementArray;
const Interval *Interval::lastInterval = nullptr;

struct COMPARE_INTERVAL_PTR
{
	auto operator()(const Interval *left, const Interval *right) const -> bool
	{
		if (left->start == right->start)
			return left->end < right->end;
		else
			return left->start < right->start;
	};
};

int main()
{
	vector<Interval> intervalArray;

	/////////////////////////////////////////////////////
	// ������ ����
	/////////////////////////////////////////////////////
	size_t valueSize;
	size_t intervalSize;

	cin >> valueSize >> intervalSize;
	Interval::elementArray.reserve(valueSize);
	intervalArray.reserve(intervalSize);

	for (size_t i = 0; i < Interval::elementArray.capacity(); i++)
	{
		int value;
		cin >> value;

		Interval::elementArray.push_back(value);
	}

	for (size_t i = 0; i < intervalArray.capacity(); i++)
	{
		size_t start;
		size_t end;

		cin >> start >> end;
		intervalArray.push_back(Interval(start - 1, end));
	}

	/////////////////////////////////////////////////////
	// �� ������ �ִ밪 ���
	/////////////////////////////////////////////////////
	vector<Interval*> intervalPtrArray(intervalArray.size());
	for (size_t i = 0; i < intervalArray.size(); i++)
		intervalPtrArray[i] = &intervalArray[i];

	// ������ �ϰ�
	sort(intervalPtrArray.begin(), intervalPtrArray.end(), COMPARE_INTERVAL_PTR());

	// ���ĵ� ������ ���� ����� �Ѵ�.
	for (size_t i = 0; i < intervalPtrArray.size(); i++)
		intervalPtrArray[i]->calcMax();

	/////////////////////////////////////////////////////
	// ��� ���
	/////////////////////////////////////////////////////
	for (size_t i = 0; i < intervalArray.size(); i++)
		cout << intervalArray[i].getMaxValue() << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}