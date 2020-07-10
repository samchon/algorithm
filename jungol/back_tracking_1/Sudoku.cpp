#include <iostream>
#include <vector>
#include <set>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

template <typename T> using Matrix = vector<vector<T>>;

/**
 * ��ǥ Ŭ����.
 */
class Point
{
public:
	/**
	 * ��
	 */
	int row;

	/**
	 * ��
	 */
	int col;

	/* ----------------------------------------------------------
		CONSTRUCTORS
	---------------------------------------------------------- */
	/**
	 * Default Constructor.
	 *
	 * ��ȿ���� ���� ��ǥ�� ǥ���ϱ� ����. 
	 * �ڹ��� nulló�� ������ �Ѵ�.
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
 * (������ ���) �� Ŭ����.
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
	 * ����κ��� ����� ���ҵ��� �Է¹���
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
	 * ��ǥ�� ���� Element accessor
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
	 * �� ����(0)�� Ž���Ͽ� ä���ִ´�.
	 */
	auto explore() -> bool
	{
		const Point &blank = findBlank();

		if (blank == Point(-1, -1))
		{
			// �� ������ ����. 
			// ��, �� ������ �� ä��� �� ������
			return true;
		}
		
		// ���� ��ǥ (�� ����) �� �� �� �ִ� �ĺ� �� ����Ʈ
		const set<int> &candidates = fetchCandidates(blank);
		if (candidates.empty() == true)
		{
			// �� �����̵�, �ĺ����� ���ٸ�, ������ ����� �ƴ϶� �ǹ�
			return false;
		}

		for (auto it = candidates.begin(); it != candidates.end(); it++)
		{
			// �� ���� ��ǥ�� ������ �ĺ������� ä�� ��
			this->at(blank) = *it;

			// �������� Ž���� ����
			if (explore() == true)
			{
				// Ž���� ������, 
				// ������ ������� Ȯ�ε�
				return true;
			}
			// ������ �ĺ����� ��ȿ���� ���� ���̶��, ���� �ĺ������� �Ѿ
			// else 
			//	continue;
		}

		// �� � �ĺ����� ������ ����� ���� �� ���ٸ�,
		this->at(blank) = 0; // ���� ��ǥ�� �ٽ� �� �������� �ΰ�
		return false; // ���и� ������
	};

private:
	/**
	 * �� ������ ã��
	 *
	 * ä�� �� �ִ� ���� ����� ���� ���� ���� �� ������ ã�´�
	 * �� ������ ������, Point(-1, -1) �� ����
	 *
	 * @return ���� ����� ���� ���� �� ���� ��ǥ Ȥ�� null
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
	 * ������ ���� ���ҵ��� ����Ѵ�
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
	 * �� ��ǥ�� ���� �� �ִ� �ĺ� ���� ������ �޾ƿ�.
	 *
	 * @param p ã���� �ϴ� �� ��ǥ.
	 * @return �ĺ� ���Ұ� ��Ʈ
	 */
	auto fetchCandidates(Point p) const -> set<int>
	{
		set<int> candidates;
		
		// �켱 ��Ʈ�� 1~9 ���� ���� �Է��صΰ�
		for (int i = 1; i <= 9; i++)
			candidates.insert(i);

		// �� ������ ���Ե� �����κ���
		for (size_t c = 0; c < this->size(); c++)
		{
			int val = this->at(p.row).at(c);

			// �̹� �����ϴ� ���Ҹ� ��Ʈ�κ��� ����
			if (candidates.count(val) != 0)
				candidates.erase(val);
		}

		// �� ������ ���Ե� ���κ���
		for (size_t r = 0; r < this->size(); r++)
		{
			int val = this->at(r).at(p.col);

			// �̹� �����ϴ� ���Ҹ� ��Ʈ�κ��� ����
			if (candidates.count(val) != 0)
				candidates.erase(val);
		}

		// 3x3 �κ� ��ķκ���
		p.row -= p.row % 3;
		p.col -= p.col % 3;

		for (size_t r = p.row; r < p.row + 3; r++)
			for (size_t c = p.col; c < p.col + 3; c++)
			{
				int val = this->at(r).at(c);

				// �̹� �����ϴ� ���Ҹ� ��Ʈ�κ��� ����
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
	 * ���� ����� ������ ����ΰ� �˻�
	 */
	auto isSudoku() const -> bool
	{
		// �� �˻�
		for (size_t r = 0; r < this->size(); r++)
			if (isSudokuRow(r) == false)
				return false;

		// �� �˻�
		for (size_t c = 0; c < this->size(); c++)
			if (isSudokuCol(c) == false)
				return false;

		// 3x3 �κ���� �˻�
		for (size_t r = 0; r < this->size(); r += 3)
			for (size_t c = 0; c < this->size(); c += 3)
				if (isSudokuArea(Point(r, c)) == false)
					return false;

		return true;
	};

private:
	/**
	 * 3x3 �κ� ����� ������ ������� �˻���
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
	 * ������ ���� ������ ����� �����ϴ� �� �˻���
	 */
	auto isSudokuRow(size_t r) const -> bool
	{
		set<int> intSet;
		for (size_t c = 0; c < this->size(); c++)
			intSet.insert(at(r).at(c));

		return intSet.size() == 9;
	};
	
	/** 
	 * ������ ���� ������ ����� �����ϴ� �� �˻���
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