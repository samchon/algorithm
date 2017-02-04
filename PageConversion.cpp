#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

/**
 * 페이지 행렬.
 *
 * 각 페이지 간의 이동에 필요한 최소 클릭수를 저장해놓은 행렬.
 * 이동이 불가한 경우에는 INT_MAX, 이동이 가능한 경우 초기값은 1.
 */
class PageMatrix
	: public vector<vector<int>>
{
private:
	typedef vector<vector<int>> super;

public:
	/**
	 * Construct from 행렬 사이즈.
	 */
	PageMatrix(size_t size)
		: super(size, vector<int>(size, INT_MAX))
	{
	};
	
	/**
	 * 막 페이지 간에 이동에 필요한 최소 클릭수를 계산한다.
	 */
	void calcDepth()
	{
		for (size_t k = 0; k < size(); k++) // 교차
			for (size_t i = 0; i < size(); i++) // 행
				for (size_t j = 0; j < size(); j++) // 열
				{
					if (i == j)
						continue;
					else if (at(i).at(k) == INT_MAX || at(k).at(j) == INT_MAX)
					{
						// 교차 경로가 존재하지 않는다면 PASS
						continue;
					}
					int &depth = at(i).at(j);
					int newDepth = at(i).at(k) + at(k).at(j);

					// 교차 경로가 기존의 경로보다 더 짧다면, 갱신한다
					depth = min(depth, newDepth);
				}
	};
	
public:
	/**
	 * 각 페이지 간 이동에 필요한 클릭수의 평균값을 계산함.
	 */
	auto calcAverage() const -> double
	{
		int nominator = 0.0;
		double denominator = (size() - 1) * size();

		for (size_t i = 0; i < size(); i++)
			for (size_t j = 0; j < size(); j++)
			{
				if (i == j || at(i).at(j) == INT_MAX)
					continue;
				else
					nominator += at(i).at(j);
			}

		return nominator / denominator;
	};
};

int main()
{
	// -------------------------------------------------
	//	데이터 구성
	// -------------------------------------------------
	// 먼저 링크 경로만 따로이 입력받는다.
	vector<pair<size_t, size_t>> linkArray;
	size_t linkSize;
	cin >> linkSize;

	size_t size = 0;

	for (size_t i = 0; i < linkSize; i++)
	{
		size_t from, to;
		cin >> from >> to;
		
		// 그 와중에 사이트 개수를 갱신해나감
		size = max(size, max(from, to));

		// 링크 배열에 추가
		linkArray.push_back({from - 1, to - 1});
	}

	// 페이지 행렬 구성
	PageMatrix stationMatrix(size);
	for (size_t i = 0; i < linkArray.size(); i++)
	{
		const pair<size_t, size_t> &link = linkArray[i];

		stationMatrix.at(link.first).at(link.second) = 1;
	}

	// -------------------------------------------------
	//	최단 경로 (클릭수) 계산
	// -------------------------------------------------
	stationMatrix.calcDepth();

	// -------------------------------------------------
	//	결과 출력
	// -------------------------------------------------
	// 소수 세 번째 자리에 고정하기 위한 C++ 함수
	cout << fixed;
	cout.precision(3);

	// 평균 클릭 횟수 출력
	cout << stationMatrix.calcAverage() << endl;

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}