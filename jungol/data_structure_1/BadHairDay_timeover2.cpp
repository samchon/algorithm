#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Cow
{
public:
	// 배열 內 index 번호.
	size_t index;

	// 소가 볼 있는 숫자.
	unsigned long long see;

	/**
	 * 기본 생성자.
	 */
	Cow()
	{
	};

	/**
	* 생성자 from see and index.
	*
	* @param index 가장 큰 소의 배열 內 index 번호.
	* @param see 가장 큰 소가 볼 있는 숫자.
	*/
	Cow(size_t index, unsigned long long see)
	{
		this->index = index;
		this->see = see;
	};
};

int main()
{
	vector<int> people;

	/////////////////////////////////////////
	// 소들의 키 배열 구성
	/////////////////////////////////////////
	size_t size;
	cin >> size;
	people.assign(size, 0);

	for (size_t i = 0; i < people.size(); i++)
		cin >> people[i];

	/////////////////////////////////////////
	// 몇 마리의 소를 볼 수 있나
	/////////////////////////////////////////
	unsigned long long totalSee = 0;
	map<int, Cow> heightMap;

	// 마지막 소는 미리 등록함
	heightMap[people.back()] = Cow(people.size() - 1, 0);

	for (long i = people.size() - 2; i >= 0; i--)
	{
		size_t index = (size_t)i;
		int height = people[i];
		unsigned long long see = 0;

		///////////////////////////////////////////////
		// 자신보다 크거나 같은 소를 찾음
		///////////////////////////////////////////////
		map<int, Cow>::iterator it = heightMap.lower_bound(height);

		if (it != heightMap.end())
		{
			// 자신보다 같거나 혹은 더 큰 소가 존재한다면
			size_t greaterIndex = it->second.index;

			// 그 사이에 그보다 더 큰 소가 없는 지 확인한다
			for (size_t j = i + 1; j < greaterIndex; j++)
				if (people[j] >= people[i])
				{
					greaterIndex = j;
					break;
				}
			
			// 그 소와 자신 사이에 소 마릿 수만큼 볼 수 있다.
			see = greaterIndex - index - 1;
		}
		else
		{
			// 자신과 같거나 더 큰 소가 아예 없다면, 
			// 현재 소가 가장 큰 소이니, 모두 볼 수 있다.
			see = totalSee + 1;
		}

		heightMap[height] = Cow(index, see);
		totalSee += see;
	}
	cout << totalSee;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}