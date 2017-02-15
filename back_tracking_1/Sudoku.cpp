#include <iostream>
#include <vector>
#include <set>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

template <typename T> using Matrix = vector<vector<T>>;

/**
 * 좌표 클래스.
 */
class Point
{
public:
	/**
	 * 행
	 */
	int row;

	/**
	 * 열
	 */
	int col;

	/* ----------------------------------------------------------
		CONSTRUCTORS
	---------------------------------------------------------- */
	/**
	 * Default Constructor.
	 *
	 * 유효하지 않은 좌표를 표현하기 위함. 
	 * 자바의 null처럼 쓰고자 한다.
	 */
	Point() 
	{
		this->row = -1;
		this->col = -1;
	};

	/**
	 * Construct from members.
	 */
	Point(int row, int col)
	{
		this->row = row;
		this->col = col;
	};

	/* ----------------------------------------------------------
		COMPARISON METHODS
	---------------------------------------------------------- */
	auto operator<(const Point &p) const -> bool
	{
		if (row == p.row)
			return col < p.col;
		else
			return row < p.row;
	};
	auto operator==(const Point &p) const -> bool
	{
		return row == p.row && col == p.col;
	};
};

/**
 * (스도쿠 행렬) 판 클래스.
 */
class Board
	: public Matrix<int>
{
private:
	typedef Matrix<int> super;

public:
	/* ----------------------------------------------------------
		CONSTRUCTORS
	---------------------------------------------------------- */
	/**
	 * Default Constructor.
	 */
	Board()
		: super(9, vector<int>(9, 0))
	{
		listen();
	};

	/**
	 * 퀴즈로부터 행렬의 원소들을 입력받음
	 */
	void listen()
	{
		for (size_t r = 0; r < this->size(); r++)
			for (size_t c = 0; c < this->size(); c++)
			{
				Point point(r, c);
				int val;

				cin >> val;
				
				this->at(point) = val;
			}
	};

	/* ----------------------------------------------------------
		ACCESSORS
	---------------------------------------------------------- */
	using super::at;

	/**
	 * 좌표를 통한 Element accessor
	 */
	auto at(const Point &p) -> int&
	{
		return at(p.row).at(p.col);
	};
	auto at(const Point &p) const -> const int&
	{
		return at(p.row).at(p.col);
	};

	/* ----------------------------------------------------------
		OPERATORS
	---------------------------------------------------------- */
public:
	/**
	 * 빈 공간(0)을 탐색하여 채워넣는다.
	 */
	auto explore() -> bool
	{
		const Point &blank = findBlank();

		if (blank == Point(-1, -1))
		{
			// 빈 공간이 없다. 
			// 즉, 빈 공간을 다 채우는 데 성공함
			return true;
		}
		
		// 현재 좌표 (빈 공간) 에 들어갈 수 있는 후보 값 리스트
		const set<int> &candidates = fetchCandidates(blank);
		if (candidates.empty() == true)
		{
			// 빈 공간이되, 후보값이 없다면, 스도쿠 행렬이 아니란 의미
			return false;
		}

		for (auto it = candidates.begin(); it != candidates.end(); it++)
		{
			// 빈 공간 좌표를 현재의 후보값으로 채운 후
			this->at(blank) = *it;

			// 지속적인 탐색을 수행
			if (explore() == true)
			{
				// 탐색이 끝나고, 
				// 스도쿠 행렬임이 확인됨
				return true;
			}
			// 현재의 후보값이 유효하지 않은 값이라면, 다음 후보값으로 넘어감
			// else 
			//	continue;
		}

		// 그 어떤 후보값도 스도쿠 행렬을 만들 수 없다면,
		this->at(blank) = 0; // 현재 좌표를 다시 빈 공간으로 두고
		return false; // 실패를 리턴함
	};

private:
	/**
	 * 빈 공간을 찾음
	 *
	 * 채울 수 있는 값의 경우의 수가 가장 작은 빈 공간을 찾는다
	 * 빈 공간이 없으면, Point(-1, -1) 을 리턴
	 *
	 * @return 가장 경우의 수가 작은 빈 공간 좌표 혹은 null
	 */
	auto findBlank() const -> Point
	{
		Point minPoint;
		size_t minSize = INT_MAX;

		for (size_t r = 0; r < this->size(); r++)
			for (size_t c = 0; c < this->size(); c++)
			{
				Point point(r, c);
				
				if (this->at(point) != 0)
					continue;

				size_t size = fetchCandidates(point).size();
				if (size < minSize)
				{
					minPoint = point;
					minSize = size;
				}
			}

		return minPoint;
	};

public:
	/* ----------------------------------------------------------
		PRINTER
	---------------------------------------------------------- */
	/**
	 * 스도쿠 판의 원소들을 출력한다
	 */
	void print() const
	{
		for (size_t r = 0; r < this->size(); r++)
		{
			for (size_t c = 0; c < this->size(); c++)
				cout << at(r).at(c) << " ";
			cout << endl;
		}
	}

private:
	/**
	 * 빈 좌표가 넣을 수 있는 후보 원소 값들을 받아옴.
	 *
	 * @param p 찾고자 하는 빈 좌표.
	 * @return 후보 원소값 셋트
	 */
	auto fetchCandidates(Point p) const -> set<int>
	{
		set<int> candidates;
		
		// 우선 세트에 1~9 까지 전부 입력해두고
		for (int i = 1; i <= 9; i++)
			candidates.insert(i);

		// 빈 공간이 포함된 행으로부터
		for (size_t c = 0; c < this->size(); c++)
		{
			int val = this->at(p.row).at(c);

			// 이미 존재하는 원소를 셋트로부터 제거
			if (candidates.count(val) != 0)
				candidates.erase(val);
		}

		// 빈 공간이 포함된 열로부터
		for (size_t r = 0; r < this->size(); r++)
		{
			int val = this->at(r).at(p.col);

			// 이미 존재하는 원소를 셋트로부터 제거
			if (candidates.count(val) != 0)
				candidates.erase(val);
		}

		// 3x3 부분 행렬로부터
		p.row -= p.row % 3;
		p.col -= p.col % 3;

		for (size_t r = p.row; r < p.row + 3; r++)
			for (size_t c = p.col; c < p.col + 3; c++)
			{
				int val = this->at(r).at(c);

				// 이미 존재하는 원소를 셋트로부터 제거
				if (candidates.count(val) != 0)
					candidates.erase(val);
			}

		return candidates;
	};

public:
	/* ----------------------------------------------------------
		INSPECTORS
	---------------------------------------------------------- */
	/**
	 * 현재 행렬이 스도쿠 행렬인가 검사
	 */
	auto isSudoku() const -> bool
	{
		// 행 검사
		for (size_t r = 0; r < this->size(); r++)
			if (isSudokuRow(r) == false)
				return false;

		// 열 검사
		for (size_t c = 0; c < this->size(); c++)
			if (isSudokuCol(c) == false)
				return false;

		// 3x3 부분행렬 검사
		for (size_t r = 0; r < this->size(); r += 3)
			for (size_t c = 0; c < this->size(); c += 3)
				if (isSudokuArea(Point(r, c)) == false)
					return false;

		return true;
	};

private:
	/**
	 * 3x3 부분 행렬이 스도쿠 행렬인지 검사함
	 */
	auto isSudokuArea(const Point &p) const -> bool
	{
		set<int> intSet;
		for (size_t r = p.row; r < p.row + 3; r++)
			for (size_t c = p.col; c < p.col + 3; c++)
				intSet.insert(at(r).at(c));

		return intSet.size() == 9;
	};

	/** 
	 * 현재의 행이 스도쿠 행렬을 만족하는 지 검사함
	 */
	auto isSudokuRow(size_t r) const -> bool
	{
		set<int> intSet;
		for (size_t c = 0; c < this->size(); c++)
			intSet.insert(at(r).at(c));

		return intSet.size() == 9;
	};
	
	/** 
	 * 현재의 열이 스도쿠 행렬을 만족하는 지 검사함
	 */
	auto isSudokuCol(size_t c) const -> bool
	{
		set<int> intSet;
		for (size_t r = 0; r < this->size(); r++)
			intSet.insert(at(r).at(c));

		return intSet.size() == 9;
	};
};

int main()
{
	Board board;
	board.explore();

	board.print();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}