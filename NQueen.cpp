#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

/**
 * ���� Ŭ����. ��ǥ�� �浹���� �޼ҵ带 ����.
 */
class Queen
{
public:
	int x;
	int y;

	Queen();
	Queen(int, int);

	/**
	* �浹 ����.
	*/
	bool hitTest(const Queen &queen) const;
};

/**
 * ��ġ ������ ����� ���� ���ϴ� Ŭ����.
 */
class QueenAllocator
{
private:
	/**
	 * ���� ����� ũ�� �� ��ġ�ؾ� �� ������ ��.
	 */
	int n;

public:
	QueenAllocator(int);

	int size() const;

private:
	/**
	 * �� Y�� ���� ������ ��� X��ǥ�� ���� ��Ʈ��ŷ �ǽ�
	 *
	 * @param N���� ������ ���� �迭. �� ��, y���� Ȯ����.
	 * @param Y��.
	 */
	int size(vector<Queen> &queenArray, int y) const;
};

int main()
{
	int size;
	cin >> size;

	QueenAllocator allocator(size);
	cout << allocator.size();
	
	return 0;
}

/* =======================================================
	ALLOCATOR
======================================================= */
QueenAllocator::QueenAllocator(int n)
{
	this->n = n;
}

int QueenAllocator::size() const
{
	vector<Queen> queenArray(n);
	int size = 0;
	int i;
	int end = (n % 2 == 0) ? n / 2 : n / 2 + 1;

	for (i = 0; i < end; i++)
	{
		queenArray[0].x = i;
		queenArray[0].y = 0;

		int mySize = this->size(queenArray, 0);
		if (i == n / 2)
			size += mySize; // Ȧ��, ��� �ڸ�
		else
			size += mySize * 2; // ¦��, �¿��Ī�̶� x2
	}

	return size;
}

int QueenAllocator::size(vector<Queen> &queenArray, int y) const
{
	////////////////////////////////
	// ���� ���հ��� �浹 �˻�
	////////////////////////////////
	for (int i = 0; i < y; i++)
		if (queenArray[i].hitTest(queenArray[y]) == true)
			return 0;

	if (y == n - 1) // ���� Y����� ����
		return 1;

	int size = 0;
	
	for (int x = 0; x < n; x++)
	{
		////////////////////////////////
		// �ߺ��� X ���ΰ�?
		////////////////////////////////
		bool duplicated = false;

		for (int j = 0; j < y; j++)
			if (x == queenArray[j].x)
			{
				duplicated = true;
				break;
			}

		if (duplicated == true)
			continue;

		////////////////////////////////
		// �� ������ ����
		////////////////////////////////
		Queen &queen = queenArray[y + 1];
		queen.x = x;
		queen.y = y + 1;

		// ���� �ܰ��
		size += this->size(queenArray, y + 1);
	}
	return size;
}

/* =======================================================
	QUEEN
======================================================= */
Queen::Queen()
{
	x = 0;
	y = 0;
}
Queen::Queen(int x, int y)
{
	this->x = x;
	this->y = y;
};

bool Queen::hitTest(const Queen &queen) const
{
	if (queen.x == x || queen.y == y)
		return true;
	else if (abs(queen.x - x) == abs(queen.y - y))
		return true;
	else
		return false;
}