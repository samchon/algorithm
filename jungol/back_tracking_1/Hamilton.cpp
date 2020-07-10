#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INT_MAX 9999
#define BOOL char // vector<bool> 은 압축을 하기에 실행속도에서 불리

vector<vector<int>> costMatrix;
vector<BOOL> visitedArray;

int calc(vector<size_t> &row);
int calc(vector<size_t> &row, size_t index);

int main()
{
	size_t size;

	// 먼저 행렬을 읽어 구성한다.
	cin >> size;
	costMatrix.assign(size, vector<int>(size, 0));
	visitedArray.assign(size, false);

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			cin >> costMatrix[i][j];

	// 백 트레킹, (가능한) 모든 경우의 수를 계산
	vector<size_t> row(size - 1, 0);

	// 결과 출력
	cout << calc(row);

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}

int calc(vector<size_t> &row)
{
	int minCost = INT_MAX;

	for (size_t i = 1; i <= row.size(); i++)
	{
		row[0] = i;

		// 현재 분기의 경로가 유효한가
		int myCost = calc(row, 0);
		if (myCost == 0)
			continue;

		minCost = min(minCost, myCost);
	}

	return minCost;
}

int calc(vector<size_t> &row, size_t index)
{
	size_t prev = (index == 0) ? 0 : row[index - 1];
	size_t now = row[index];

	int cost = costMatrix[prev][now];
	
	if (cost == 0) // 현재 분기가 유효한가?
	{
		return 0;
	}
	else if (index == row.size() - 1) // 최종 장소까지 도착하였는가
	{
		int lastCost = costMatrix[row.back()][0];
		
		if (lastCost == 0)
			return 0;
		else
			return cost + lastCost;
	}

	int minCost = INT_MAX; // 최소 비용
	visitedArray[now] = true; // 방문지점에 추가

	for (size_t i = 1; i <= row.size(); i++)
	{
		// 이미 방문한 지점은 건너뜀
		if (visitedArray[i] == true)
			continue;

		// 다음 경로에 대해 등록하고 계산을 함
		row[index + 1] = i;
		int myCost = calc(row, index + 1);

		// 유효시, 최소비용 갱신
		if (myCost != 0)
			minCost = min(minCost, cost + myCost);
	}

	visitedArray[now] = false;
	return minCost;
}