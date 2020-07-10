#include <iostream>
#include <vector>
#include <map>

#include <algorithm>

using namespace std;

void listen(map<int, size_t> &map, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		int key;
		cin >> key;

		map.insert({ key, i });
	}
}

int main()
{
	// ---------------------------------------
	//	데이터 입력
	// ---------------------------------------
	map<int, size_t> topMap;
	map<int, size_t> bottomMap;

	vector<int> missKeyArray;

	size_t size;
	cin >> size;

	listen(topMap, size);
	listen(bottomMap, size);

	// ---------------------------------------
	//	교차 케이블 쌍의 수를 구함
	// ---------------------------------------
	size_t cable = 0;
	
	for (auto it = topMap.begin(); it != topMap.end(); it++)
		if (it->second != bottomMap[it->first])
		{
			// 위 아래간 위치가 다른 케이블 번호를 등록함
			missKeyArray.push_back(it->first);
		}

	for (size_t i = 0; i < missKeyArray.size() - 1; i++)
	{
		int myKey = missKeyArray[i];
		pair<size_t, size_t> myRange = {topMap[myKey], bottomMap[myKey]};

		for (size_t j = i + 1; j < missKeyArray.size(); j++)
		{
			int yourKey = missKeyArray[j];
			pair<size_t, size_t> yourRange = {topMap[yourKey], bottomMap[yourKey]};

			// 교차되는 지 여부를 검사함
			if (myRange.first < yourRange.first && myRange.second > yourRange.second)
			{
				cable++;
			}
			else if (myRange.first > yourRange.first && myRange.second < yourRange.second)
				cable++;
		}
	}

	cout << cable << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}