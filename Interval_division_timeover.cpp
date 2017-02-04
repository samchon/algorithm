#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ElementArray
	: public vector<int>
{
private:
	typedef vector<int> super;

public:
	using super::super;

	auto calcMax(size_t begin, size_t end) -> int
	{
		// 최대값
		int val;

		if (end - begin >= 2)
		{
			// 구하려는 구간 크기가 2를 넘어서면
			// 분할하여 계산
			size_t middle = (begin + end) / 2;

			int front = calcMax(begin, middle); // 앞쪽 반
			int back = calcMax(middle, end); // 뒷쪽 반

			val = max(front, back);
		}
		else
		{
			// 범위 내 FULL SCANNING
			val = this->at(begin);

			for (size_t i = begin + 1; i < end; i++)
				val = max(val, this->at(i));
		}

		return val;
	};
};

int main()
{
	ElementArray elementArray;
	
	/////////////////////////////////////////////////////
	// 데이터 구성
	/////////////////////////////////////////////////////
	size_t elementSize, intervalSize;
	cin >> elementSize >> intervalSize;

	elementArray.assign(elementSize, 0);
	
	// 각 원소 입력
	for (size_t i = 0; i < elementArray.size(); i++)
		cin >> elementArray[i];

	/////////////////////////////////////////////////////
	// 각 구간별 최대값 계산 & 출력
	/////////////////////////////////////////////////////
	for (size_t i = 0; i < intervalSize; i++)
	{
		size_t begin;
		size_t end;

		cin >> begin >> end;
		cout << elementArray.calcMax(begin - 1, end) << endl;
	}

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}