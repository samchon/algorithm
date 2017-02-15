#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

/**
* ��ġ ������ ����� ���� ���ϴ� Ŭ����.
*/
class QueenAllocator
{
private:
	size_t n;

public:
	QueenAllocator(size_t);

	size_t size() const;
};

/**
* ����. ��ǥ�� �浹���� �޼ҵ带 ����.
*/
class Queen
{
public:
	int x;
	int y;

	Queen();
	Queen(int, int);

	bool hitTest(const Queen &queen) const;
};

int main()
{
	size_t size;
	cin >> size;

	QueenAllocator allocator(size);
	cout << allocator.size();

	//#ifdef _WIN32
	//	system("pause");
	//#endif

	return 0;
}

/* =======================================================
	ALLOCATOR
======================================================= */
QueenAllocator::QueenAllocator(size_t n)
{
	this->n = n;
}

size_t QueenAllocator::size() const
{
	size_t N = n*n;
	size_t R = n;

	// ������ ���� ��Ʈ����ũ
	vector<bool> bitmask(N);
	std::fill(bitmask.begin(), bitmask.begin() + R, true);

	size_t size = 0;

	do
	{
		////////////////////
		// �� ��ġ
		////////////////////
		vector<Queen> queenArray(R);
		bool hit = false;

		size_t k = 0;
		for (size_t j = 0; j < N; j++)
		{
			if (bitmask[j] == false)
				continue;

			queenArray[k].x = j % n;
			queenArray[k].y = j / n;
			k++;
		}

		////////////////////
		// �浹 ����
		////////////////////
		for (size_t ii = 0; ii < queenArray.size(); ii++)
		{
			for (size_t jj = ii + 1; jj < queenArray.size(); jj++)
				if (queenArray[ii].hitTest(queenArray[jj]) == true)
				{
					hit = true;
					break;
				}
			if (hit == true)
				break;
		}

		if (hit == false) // �浹���� �ʾҴٸ� +1
			size++;;
	} while (prev_permutation(bitmask.begin(), bitmask.end()));

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
	if (x == queen.x || y == queen.y)
		return true;
	else if (abs(x - queen.x) == abs(y - queen.y))
		return true;
	else
		return false;
}