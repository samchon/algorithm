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
			// 처음 구하는 MAX 값이거나, 
			// 혹은 이전 최대값 index가 현재의 범위를 벗어나는 것이라면
			// FULL SCAN을 한다
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
			// 이전에 구해놓은 MAX 값이 있고, 이 MAX의 index가 현재 범위 내에도 있다면,
			// 이를 토대로 PARTIAL SCANNING 만 수행한다.
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
	// 데이터 구성
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
	// 각 구간별 최대값 계산
	/////////////////////////////////////////////////////
	vector<Interval*> intervalPtrArray(intervalArray.size());
	for (size_t i = 0; i < intervalArray.size(); i++)
		intervalPtrArray[i] = &intervalArray[i];

	// 정렬을 하고
	sort(intervalPtrArray.begin(), intervalPtrArray.end(), COMPARE_INTERVAL_PTR());

	// 정렬된 순서에 따라 계산을 한다.
	for (size_t i = 0; i < intervalPtrArray.size(); i++)
		intervalPtrArray[i]->calcMax();

	/////////////////////////////////////////////////////
	// 결과 출력
	/////////////////////////////////////////////////////
	for (size_t i = 0; i < intervalArray.size(); i++)
		cout << intervalArray[i].getMaxValue() << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}