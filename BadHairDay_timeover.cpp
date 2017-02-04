#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Cow
{
public:
	// 가장 큰 소의 배열 內 index 번호
	size_t index;

	// 가장 큰 소가 볼 있는 숫자
	long long see;

	/**
	 * 생성자 from see and index.
	 *
	 * @param see 가장 큰 소가 볼 있는 숫자
	 * @param index 가장 큰 소의 배열 內 index 번호
	 */
	Cow(size_t index, long long see)
	{
		this->see = see;
		this->index = index;
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
	long long see = 0;
	Cow maxPair(people.size() - 1, 0);

	for (int i = people.size() - 2; i >= 0; i--)
	{
		// 새로운 소가 기존의 가장 큰 소보다 더 클 때,
		if (people[i] > people[maxPair.index])
		{
			// 새로운 소는 기존의 가장 큰 소와의 index 차이에 더하여
			// 기존의 소가 봤던 모든 소들도 볼 수 있다.
			long long mySee = (maxPair.index - i) + maxPair.see;
			
			maxPair = Cow(i, mySee);
			see += mySee;
		}
		else
			for (int j = i + 1; j < people.size(); j++)
				if (people[i] > people[j])
					see++;
				else
					break;
	}
	cout << see;
	return 0;
}