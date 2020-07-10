#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

class Sequence
{
public:
	size_t see;
	int person;

public:
	Sequence(size_t see)
	{
		this->see = see;
	};
};

int main()
{
	deque<int> people; // 사람들의 키를 담은 배열
	vector<Sequence> sequenceArray;
	size_t size;

	/////////////////////////////////////////
	// 데이터 입력
	/////////////////////////////////////////
	cin >> size;
	people.assign(size, -1);
	sequenceArray.reserve(size);

	for (size_t i = 0; i < size; i++)
		cin >> people[i];

	for (size_t i = 0; i < size; i++)
	{
		size_t see;
		cin >> see;

		sequenceArray.push_back(Sequence(see));
	}

	/////////////////////////////////////////
	// 연산 수행
	/////////////////////////////////////////
	// 키 순서에 따른 정렬
	sort(people.begin(), people.end());

	// for (int i = sequenceArray.size() - 1; i >= 0; i--)
	// 위 코드와 같다. 다만, 최적화를 위해 iterator 를 대신 사용함
	for (auto it = sequenceArray.rbegin(); it != sequenceArray.rend(); it++)
	{
		// 뒤에서부터 볼 수 있는 인원 수 (see) 를 index 로
		// people 에서 뽑아오면 됨
		it->person = people[it->see];

		// 그 후에, 해당 index (see) 를 people로부터 지워주면 끝
		people.erase(people.begin() + it->see);
	}

	for (auto it = sequenceArray.begin(); it != sequenceArray.end(); it++)
		cout << it->person << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}