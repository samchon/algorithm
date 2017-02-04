#include <iostream>
#include <queue>
#include <set>

using namespace std;

/**
 * ü�� ���� ��ü. ��� �� ������ ����.
 */
class ChessObject
{
public:
	int row;
	int col;

public:
	ChessObject(int row, int col);
	ChessObject(const ChessObject &obj);
	virtual ~ChessObject();
};

/**
 * ü����.
 */
class Board
	: public ChessObject
{
private:
	typedef ChessObject super;

public:
	Board(int row, int col);
	virtual ~Board();
};

/**
 * ����.
 */
class Pawn
	: public ChessObject
{
private:
	typedef ChessObject super;

public:
	Pawn(int row, int col);
	virtual ~Pawn();
};

/**
 * ��.
 */
class Horse
	: public ChessObject
{
private:
	typedef ChessObject super;

public:
	/**
	 * ü���� ����
	 */
	Board *board;

	/**
	 * �̵� Ƚ��
	 */
	int movement;

	/**
	 * �̹� �湮�ߴ� ����
	 */
	static set< pair<int, int> > s_visited;

public:
	Horse(Board *board, int row, int col);
	Horse(const Horse &horse);
	virtual ~Horse() {};

	/**
	 * �浹 �˻�. ���� ��Ҵ°�?
	 */
	bool hitTest(const Pawn &pawn) const;

	/**
	 * ���� ������ ��ȣ�� �����ӿ� ���� �̵��Ѵ�.
	 *
	 * ��ȿ�� �˻� ���� �����Ѵ�.
	 *	- ü���� ���� ������ �ִ���, 
	 *	- �̹� �湮�� ������ �� ������ �ʾҴ���.
	 */
	bool move(int index);
};

class Chess
{
private:
	Board *board;
	Horse *horse;
	Pawn *pawn;

public:
	Chess(Board *board, Horse *horse, Pawn *pawn);

	int chase() const;
};

int main()
{
	int row, col;
	int horseRow, horseCol;
	int pawnRow, pawnCol;

	// LISTENS
	cin >> row;			cin >> col;
	cin >> horseRow;	cin >> horseCol;
	cin >> pawnRow;		cin >> pawnCol;

	// CONSTRUCTS
	Board board(row, col);
	Horse horse(&board, horseRow, horseCol);
	Pawn pawn(pawnRow, pawnCol);

	Chess chess(&board, &horse, &pawn);
	cout << chess.chase();

	return 0;
}

/* =======================================================
	CHESS
======================================================= */
Chess::Chess(Board *board, Horse *horse, Pawn *pawn)
{
	this->board = board;
	this->horse = horse;
	this->pawn = pawn;
}

int Chess::chase() const
{
	queue<Horse> horseQueue;
	horseQueue.push(*this->horse);

	while (horseQueue.empty() == false)
	{
		// ������ ���� ����
		const Horse horse = horseQueue.front();
		horseQueue.pop();

		for (int i = 0; i < 8; i++)
		{
			// ������ ����
			Horse myHorse(horse);

			// �̵�
			if (myHorse.move(i) == false)
				continue;

			// ���� ��Ҵ°�?
			if (myHorse.hitTest(*pawn) == true)
				return myHorse.movement;

			horseQueue.push(myHorse);
		}
	}

	return -1;
}

/* =======================================================
	HORSE
======================================================= */
set< pair<int, int> > Horse::s_visited;

Horse::Horse(Board *board, int row, int col)
	: super(row, col)
{
	this->board = board;
	this->movement = 0;
}
Horse::Horse(const Horse &horse)
	: super(horse)
{
	this->board = horse.board;
	this->movement = horse.movement;
}

bool Horse::hitTest(const Pawn &pawn) const
{
	return row == pawn.row && col == pawn.col;
}

bool Horse::move(int index)
{
	////////////////////////////////
	// ������� �� ũ��
	////////////////////////////////
	int rowSign, colSign;
	int rowStep, colStep;

	rowSign = (index == 0 || index == 1 || index == 6 || index == 7) ? -1 : 1;
	colSign = (index < 4) ? -1 : 1;

	rowStep = (index == 0 || index == 3 || index == 4 || index == 7) ? 2 : 1;
	colStep = (rowStep == 2) ? 1 : 2;

	row += rowSign * rowStep;
	col += colSign * colStep;

	////////////////////////////////
	// ��ȿ�� ����
	////////////////////////////////
	if (row <= 0 || row > board->row || col <= 0 || col > board->col) // ������ ���
		return false;
	else if (s_visited.count(pair<int, int>(row, col)) != 0) // �̹� �湮�ߴ� ����
		return false;
	
	this->movement++;
	s_visited.insert(pair<int, int>(row, col));

	return true;
};

/* =======================================================
	CHESS_OBJECTS
		- PAWN
		- BOARD
======================================================= */
ChessObject::ChessObject(int row, int col)
{
	this->row = row;
	this->col = col;
};
ChessObject::ChessObject(const ChessObject &obj)
{
	this->row = obj.row;
	this->col = obj.col;
}
ChessObject::~ChessObject()
{
}

Pawn::Pawn(int row, int col)
	: super(row, col)
{
}
Pawn::~Pawn()
{
}

Board::Board(int row, int col)
	: super(row, col)
{
}
Board::~Board()
{
}