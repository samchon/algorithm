#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INT_MAX 9999
#define BOOL char // vector<bool> �� ������ �ϱ⿡ ����ӵ����� �Ҹ�

vector<vector<int>> costMatrix;
vector<BOOL> visitedArray;

int calc(vector<size_t> &row);
int calc(vector<size_t> &row, size_t index);

int main()
{
	size_t size;

	// ���� ����� �о� �����Ѵ�.
	cin >> size;
	costMatrix.assign(size, vector<int>(size, 0));
	visitedArray.assign(size, false);

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			cin >> costMatrix[i][j];

	// �� Ʈ��ŷ, (������) ��� ����� ���� ���
	vector<size_t> row(size - 1, 0);

	// ��� ���
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

		// ���� �б��� ��ΰ� ��ȿ�Ѱ�
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
	
	if (cost == 0) // ���� �бⰡ ��ȿ�Ѱ�?
	{
		return 0;
	}
	else if (index == row.size() - 1) // ���� ��ұ��� �����Ͽ��°�
	{
		int lastCost = costMatrix[row.back()][0];
		
		if (lastCost == 0)
			return 0;
		else
			return cost + lastCost;
	}

	int minCost = INT_MAX; // �ּ� ���
	visitedArray[now] = true; // �湮������ �߰�

	for (size_t i = 1; i <= row.size(); i++)
	{
		// �̹� �湮�� ������ �ǳʶ�
		if (visitedArray[i] == true)
			continue;

		// ���� ��ο� ���� ����ϰ� ����� ��
		row[index + 1] = i;
		int myCost = calc(row, index + 1);

		// ��ȿ��, �ּҺ�� ����
		if (myCost != 0)
			minCost = min(minCost, cost + myCost);
	}

	visitedArray[now] = false;
	return minCost;
}