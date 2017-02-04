#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

/**
* 배치 가능한 경우의 수를 구하는 클래스.
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
* 여왕. 좌표와 충돌감지 메소드를 가짐.
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

	// 조합을 위한 비트마스크
	vector<bool> bitmask(N);
	std::fill(bitmask.begin(), bitmask.begin() + R, true);

	size_t size = 0;

	do
	{
		////////////////////
		// 퀸 배치
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
		// 충돌 감지
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

		if (hit == false) // 충돌하지 않았다면 +1
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