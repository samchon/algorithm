#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

int main()
{
	int value; // 찾고자 하는 금액
	set<int> coinSet; // 동전 종류의 셋.
	vector<int> countArray; // 각 값(금액)에 대해 사용된 동전의 수.

	////////////////////////////////
	// 읽기
	////////////////////////////////
	// 동전 개수
	int coinSize;
	cin >> coinSize;

	// 각각의 동전 값 읽기
	for (int i = 0; i < coinSize; i++)
	{
		int coin;
		cin >> coin;

		// 같은 값의 동전이 중복되서 들어오기도 한다.
		// 이를 방지키 위해 set 사용
		coinSet.insert(coin);
	}

	// 총 금액 읽기
	cin >> value;
	countArray.assign(value + 1, INT_MAX);

	////////////////////////////////
	// 카운팅
	////////////////////////////////
	for (set<int>::iterator it = coinSet.begin(); it != coinSet.end(); it++)
	{
		int coin = *it;
		countArray[coin] = 1; //동전 1개 = 해당 금액

		for (int j = coin; j <= value; j++)
		{
			// 이전에도 아무 동전이 사용된 게 아니라면, continue
			// coin = 5, index = 25 이라면, 이전 index = 20일 때, 사용된 동전의 개수
			if (countArray[j - coin] == INT_MAX)
				continue;

			countArray[j] = 
				std::min
				(
					countArray[j], // 기존의 개수와
					countArray[j - coin] + 1 // 해당 동전(coin)을 하나 더 사용하는 것
				);
		}
	}

	if (countArray[value] == INT_MAX)
		cout << "impossible";
	else
		cout << countArray[value];

	return 0;
}