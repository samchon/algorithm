#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* ===========================================
	10��°���� �ð��ʰ� (3.3��)
		��Ʈ��ŷ���� ��ȿ���� ���� �� 
		�ߵ��� �Ÿ� �� �־�� ��
=========================================== */

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

/**
 * ����� �� �� N! ������
 */
class FactorialGenerator
{
private:
	size_t n;
	size_t size_;
	vector<size_t> atomArray;

public:
	FactorialGenerator(size_t n)
	{
		this->n = n;

		size_ = n;
		for (size_t i = n - 1; i >= 1; i--)
			size_ *= i;

		atomArray.assign(n, 0);
		for (size_t i = 0; i < n; i++)
			atomArray[i] = i;
	};

	auto size() const -> size_t
	{
		return size_;
	};

	/**
	 * Index��° ����� ���� �޾ƿ´�.
	 */
	auto at(size_t index) const -> vector<size_t>
	{
		// �ϴ� 0 ~ n-1 ���� ��ȣ�� ��� ���� �迭�� �����
		vector<size_t> atomArray = this->atomArray;
		vector<size_t> row(n, 0);

		for (size_t i = 0; i < n; i++)
		{
			size_t item = index % atomArray.size(); // index�� #������ �������� �޾ƿ�
			row[i] = atomArray[item]; // �� ��ȣ��� ����� ���� Ȯ����

			index = index / atomArray.size(); // ���� ������ ���� index�� ����
			atomArray.erase(atomArray.begin() + item); // ���� ����� ��ȣ item�� ����
		}

		return move(row); // �ణ�� ����ȭ�� ���� �̵������� ���
	};
};

int main()
{
	vector<vector<int>> costMatrix;
	size_t size;

	// ���� ����� �о� �����Ѵ�.
	cin >> size;
	costMatrix.assign(size, vector<int>(size, 1));

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			cin >> costMatrix[i][j];

	////////////////////////////////////////////
	// ��� ����� ���� ���
	////////////////////////////////////////////
	FactorialGenerator factorial(size - 1);
	vector<size_t> row(size - 1, 0);
	int minCost = 9999;

	for (size_t i = 0; i < factorial.size(); i++)
	{
		// indexed ����� ��
		// 0 ������ ����ϴ� row[i] + 1�� �� ��� ��
		const vector<size_t> &row = factorial.at(i); 

		int cost = 0; // ���� ���
		bool valid = true; // ��ȿ�� ����

		size_t prev = 0; // ���� index

		for (size_t j = 0; j < row.size(); j++)
		{
			size_t next = row[j] + 1;

			// ���� index���� �� �������� ���ϴ� ���� ��ȿ�Ѱ� �˻�
			if (costMatrix[prev][next] == 0)
			{
				// ��ȿ�� ��
				valid = false;
				break;
			}
			else
			{
				// ��ȿ�ϴٸ� ��뿡 ����
				cost += costMatrix[prev][next];
			}
			prev = next;
		}

		// �װ� ��ȿ���� �� �ƴ϶�,
		// 0�� �������� �ٽ� ���ƿ� �� �ֱ���� �ؾ� �Ѵ�.
		if (valid == true && costMatrix[prev][0] != 0)
		{
			// �ּҺ�� �����
			minCost = min(minCost, cost + costMatrix[prev][0]);
		}
	}

	cout << minCost;

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}