#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class ElementArray
	: public vector<int>
{
private:
	typedef vector<int> super;

	map<pair<size_t, size_t>, int> intervalMap;

public:
	using super::super;

	auto calcMax(size_t begin, size_t end) -> int
	{
		auto it = intervalMap.find({ begin, end });
		{
			// 이미 구해놨던 구간이면, 이를 사용
			if (it != intervalMap.end())
				return it->second;
		}

		// 최대값
		int val;

		if (end - begin >= 2)
		{
			// 구하려는 구간 크기가 2를 넘어서면
			// 분할하여 계산
			// 그래야 map의 index 적중률이 높아진다
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

		// 새로이 구한 최대값을 map에 index key와 함께 저장
		intervalMap[{begin, end}] = val;

		return val;
	};
};

int main()
{
	ElementArray elementArray;
	vector<pair<size_t, size_t>> intervalArray;

	/////////////////////////////////////////////////////
	// 데이터 구성
	/////////////////////////////////////////////////////
	size_t elementSize, intervalSize;
	cin >> elementSize >> intervalSize;

	elementArray.assign(elementSize, 0);
	intervalArray.assign(intervalSize, {0, 0});

	// 각 원소 입력
	for (size_t i = 0; i < elementArray.size(); i++)
		cin >> elementArray[i];

	// 각 구간정보 입력
	for (size_t i = 0; i < intervalArray.size(); i++)
	{
		pair<size_t, size_t> &interval = intervalArray[i];

		cin >> interval.first; 
		interval.first--; // 1을 차감해 줌
		cin >> interval.second;
	}

	/////////////////////////////////////////////////////
	// 각 구간별 최대값 계산 & 출력
	/////////////////////////////////////////////////////
	for (size_t i = 0; i < intervalArray.size(); i++)
	{
		pair<size_t, size_t> &interval = intervalArray[i];

		cout << elementArray.calcMax(interval.first, interval.second) << endl;
	}

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}