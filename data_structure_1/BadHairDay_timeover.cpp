#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Cow
{
public:
	// ���� ū ���� �迭 Ү index ��ȣ
	size_t index;

	// ���� ū �Ұ� �� �ִ� ����
	long long see;

	/**
	 * ������ from see and index.
	 *
	 * @param see ���� ū �Ұ� �� �ִ� ����
	 * @param index ���� ū ���� �迭 Ү index ��ȣ
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
	// �ҵ��� Ű �迭 ����
	/////////////////////////////////////////
	size_t size;
	cin >> size;
	people.assign(size, 0);

	for (size_t i = 0; i < people.size(); i++)
		cin >> people[i];

	/////////////////////////////////////////
	// �� ������ �Ҹ� �� �� �ֳ�
	/////////////////////////////////////////
	long long see = 0;
	Cow maxPair(people.size() - 1, 0);

	for (int i = people.size() - 2; i >= 0; i--)
	{
		// ���ο� �Ұ� ������ ���� ū �Һ��� �� Ŭ ��,
		if (people[i] > people[maxPair.index])
		{
			// ���ο� �Ҵ� ������ ���� ū �ҿ��� index ���̿� ���Ͽ�
			// ������ �Ұ� �ô� ��� �ҵ鵵 �� �� �ִ�.
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