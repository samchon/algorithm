#include <iostream>
#include <queue>
#include <set>

using namespace std;

/**
 * 체스 공통 객체. 행과 열 정보를 가짐.
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
 * 체스판.
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
 * 병정.
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
 * 말.
 */
class Horse
	: public ChessObject
{
private:
	typedef ChessObject super;

public:
	/**
	 * 체스판 정보
	 */
	Board *board;

	/**
	 * 이동 횟수
	 */
	int movement;

	/**
	 * 이미 방문했던 지점
	 */
	static set< pair<int, int> > s_visited;

public:
	Horse(Board *board, int row, int col);
	Horse(const Horse &horse);
	virtual ~Horse() {};

	/**
	 * 충돌 검사. 졸을 잡았는가?
	 */
	bool hitTest(const Pawn &pawn) const;

	/**
	 * 말을 지정된 번호의 움직임에 따라 이동한다.
	 *
	 * 유효성 검사 또한 수행한다.
	 *	- 체스판 위에 온전히 있는지, 
	 *	- 이미 방문한 지점을 또 가지는 않았는지.
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
		// 복제를 위한 샘플
		const Horse horse = horseQueue.front();
		horseQueue.pop();

		for (int i = 0; i < 8; i++)
		{
			// 샘플을 복제
			Horse myHorse(horse);

			// 이동
			if (myHorse.move(i) == false)
				continue;

			// 졸을 잡았는가?
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
	// 진행방향 및 크기
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
	// 유효성 검증
	////////////////////////////////
	if (row <= 0 || row > board->row || col <= 0 || col > board->col) // 범위를 벗어남
		return false;
	else if (s_visited.count(pair<int, int>(row, col)) != 0) // 이미 방문했던 지점
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