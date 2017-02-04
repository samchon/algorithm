#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define INT_MAX 9999

/**
 * 좌표 클래스
 */
class Point
{
public:
	/**
	 * 행
	 */
	size_t row;

	/**
	 * 열
	 */
	size_t col;

public:
	/**
	 * Construct from 좌표.
	 */
	Point(size_t row, size_t col)
	{
		this->row = row;
		this->col = col;
	};

	/**
	 * 두 좌표가 같은 지 비교
	 */
	auto operator==(const Point &obj) const -> bool
	{
		return row == obj.row && col == obj.col;
	};
};

/**
 * 행렬, 배열의 배열.
 *
 * @tparam T 원소 타입
 */
template <typename T> using Matrix = vector<vector<T>>;

/**
 * 등산로 및 등산로의 각 지점 간 이동에 소요되는 힘을 담은 행렬 클래스
 *
 * 이동 간에 소요되는 힘을 곗ㄴ하는 함수 또한 가지고 있다.
 */
class Mountain
	: public Matrix<int>
{
private:
	typedef Matrix<int> super;

public:
	/* -----------------------------------------------------
		CONSTRUCTORS
	----------------------------------------------------- */
	/**
	 * Construct from 정방행렬의 크기.
	 */
	Mountain(size_t size)
		: super(size, vector<int>(size, -1))
	{
		// 데이터 입력
		for (size_t r = 0; r < size; r++)
			for (size_t c = 0; c < size; c++)
				cin >> at(r).at(c);
	};

	/* -----------------------------------------------------
		ACCESSORS
	----------------------------------------------------- */
	using super::at;

	auto at(const Point &p) const -> const int&
	{
		return at(p.row).at(p.col);
	};

	/* -----------------------------------------------------
		FINDERS
	----------------------------------------------------- */
	/**
	 * 변두리 지점으로 가는 데 있어 가장 적게 소요되는 힘을 구함
	 *
	 * 각 변두리로부터 정상으로 가는 길을 찾는 것은 timeover가 났으니
	 * 역으로 정상에서 변두리로 가는 데 가장 적은 힘이 소요되는 길을 찾아본다
	 *
	 * @param start 시작지점 (퀴즈에서 주는 목표지점)
	 * @return 최소 소요 힘
	 */
	auto calcPower(const Point &start) const -> int
	{
		Matrix<int> visited(this->size(), vector<int>(this->size(), INT_MAX));

		return calcPower(start, start, visited, 0);
	};

private:
	/**
	* 각 지점간 이동시에 소요되는 힘을 계산
	*
	* @param prev 이전 지점
	* @param now 현재 지점
	* @param endP 목표 지점
	* @param visited 각 지점에 방문했을 때 소요된 최소 시간을 담은 행렬
	* @param step 현재까지 소모한 시간
	*
	* @return 최소 소요 힘
	*/
	auto calcPower
		(
			const Point &prev, const Point &now,
			Matrix<int> &visited, int step
		) const -> int
	{
		// -------------------------------------------
		//	전처리
		// -------------------------------------------
		if (now.row >= this->size() || now.col >= this->size())
		{
			// 범위를 벗어남 -> 출발지로 되돌아갔다
			return step + (int)pow(this->at(prev), 2);
		}

		// 현재까지 소모한 힘을 계산
		// 역으로 이동하기에 계산이 반대로 되야 함
		if (this->at(now) > this->at(prev))
		{
			// 오르막길을 오를 때는 
			// (거꾸로 되돌아감, 원래는 내리막길)
			// 높이 차의만큼 힘이 소요되며
			step += this->at(now) - this->at(prev);
		}
		else if (this->at(now) < this->at(prev))
		{
			// 내리막길을 걸을 때는 
			// (거꾸로 되돌아감, 원래는 오르막길)
			// 높이 차의 제곱만큼의 힘을 소요함
			step += pow(this->at(prev) - this->at(now), 2);
		} 
		// 평지를 걸을 때는 힘의 소모가 없다

		// -------------------------------------------
		//	재귀탐색 종료
		// -------------------------------------------
		if (visited[now.row][now.col] <= step)
		{
			// 현재 지점을, 더 적은 힘을 들여 방문할 수 있는 방법이 있다
			// 즉 좋지 못한 경로로 들어섬
			return INT_MAX;
		}

		// -------------------------------------------
		//	재귀 탐색
		// -------------------------------------------
		// 현재의 소요시간을 행렬에 기록
		visited[now.row][now.col] = step;

		int power = min
			({
				calcPower(now, Point(now.row - 1, now.col), visited, step), // 상
				calcPower(now, Point(now.row + 1, now.col), visited, step), // 하
				calcPower(now, Point(now.row, now.col - 1), visited, step), // 좌
				calcPower(now, Point(now.row, now.col + 1), visited, step)  // 우
			});

		return power;
	};
};

int main()
{
/*
5
3 3
1 2 4 3 2
1 3 5 4 4
2 3 6 5 1
3 1 4 1 3
2 3 3 5 3
*/
	size_t size, destRow, destCol;
	cin >> size >> destRow >> destCol;

	Mountain mountain(size);
	cout << mountain.calcPower(Point(destRow - 1, destCol - 1));

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}