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
	deque<int> people; // ������� Ű�� ���� �迭
	vector<Sequence> sequenceArray;
	size_t size;

	/////////////////////////////////////////
	// ������ �Է�
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
	// ���� ����
	/////////////////////////////////////////
	// Ű ������ ���� ����
	sort(people.begin(), people.end());

	// for (int i = sequenceArray.size() - 1; i >= 0; i--)
	// �� �ڵ�� ����. �ٸ�, ����ȭ�� ���� iterator �� ��� �����
	for (auto it = sequenceArray.rbegin(); it != sequenceArray.rend(); it++)
	{
		// �ڿ������� �� �� �ִ� �ο� �� (see) �� index ��
		// people ���� �̾ƿ��� ��
		it->person = people[it->see];

		// �� �Ŀ�, �ش� index (see) �� people�κ��� �����ָ� ��
		people.erase(people.begin() + it->see);
	}

	for (auto it = sequenceArray.begin(); it != sequenceArray.end(); it++)
		cout << it->person << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}