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
	int value; // ã���� �ϴ� �ݾ�
	set<int> coinSet; // ���� ������ ��.
	vector<int> countArray; // �� ��(�ݾ�)�� ���� ���� ������ ��.

	////////////////////////////////
	// �б�
	////////////////////////////////
	// ���� ����
	int coinSize;
	cin >> coinSize;

	// ������ ���� �� �б�
	for (int i = 0; i < coinSize; i++)
	{
		int coin;
		cin >> coin;

		// ���� ���� ������ �ߺ��Ǽ� �����⵵ �Ѵ�.
		// �̸� ����Ű ���� set ���
		coinSet.insert(coin);
	}

	// �� �ݾ� �б�
	cin >> value;
	countArray.assign(value + 1, INT_MAX);

	////////////////////////////////
	// ī����
	////////////////////////////////
	for (set<int>::iterator it = coinSet.begin(); it != coinSet.end(); it++)
	{
		int coin = *it;
		countArray[coin] = 1; //���� 1�� = �ش� �ݾ�

		for (int j = coin; j <= value; j++)
		{
			// �������� �ƹ� ������ ���� �� �ƴ϶��, continue
			// coin = 5, index = 25 �̶��, ���� index = 20�� ��, ���� ������ ����
			if (countArray[j - coin] == INT_MAX)
				continue;

			countArray[j] = 
				std::min
				(
					countArray[j], // ������ ������
					countArray[j - coin] + 1 // �ش� ����(coin)�� �ϳ� �� ����ϴ� ��
				);
		}
	}

	if (countArray[value] == INT_MAX)
		cout << "impossible";
	else
		cout << countArray[value];

	return 0;
}