#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

/**
 * 여왕 클래스. 좌표와 충돌감지 메소드를 가짐.
 */
class Queen
{
public:
	int x;
	int y;

	Queen();
	Queen(int, int);

	/**
	* 충돌 감지.
	*/
	bool hitTest(const Queen &queen) const;
};

/**
 * 배치 가능한 경우의 수를 구하는 클래스.
 */
class QueenAllocator
{
private:
	/**
	 * 정방 행렬의 크기 및 배치해야 할 여왕의 수.
	 */
	int n;

public:
	QueenAllocator(int);

	int size() const;

private:
	/**
	 * 각 Y축 별로 가능한 모든 X좌표에 대해 백트래킹 실시
	 *
	 * @param N개의 여왕을 담은 배열. 이 중, y개만 확정됨.
	 * @param Y축.
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
			size += mySize; // 홀수, 가운데 자리
		else
			size += mySize * 2; // 짝수, 좌우대칭이라 x2
	}

	return size;
}

int QueenAllocator::size(vector<Queen> &queenArray, int y) const
{
	////////////////////////////////
	// 기존 여왕과의 충돌 검사
	////////////////////////////////
	for (int i = 0; i < y; i++)
		if (queenArray[i].hitTest(queenArray[y]) == true)
			return 0;

	if (y == n - 1) // 최종 Y축까지 도달
		return 1;

	int size = 0;
	
	for (int x = 0; x < n; x++)
	{
		////////////////////////////////
		// 중복된 X 축인가?
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
		// 새 여왕을 만듦
		////////////////////////////////
		Queen &queen = queenArray[y + 1];
		queen.x = x;
		queen.y = y + 1;

		// 다음 단계로
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