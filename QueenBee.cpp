#include <iostream>
#include <array>
#include <vector>
#include <string>

using namespace std;

class Follower
{
private:
	string data_;

public:
	/* ---------------------------------------------------
		CONSTRUCTORS
	--------------------------------------------------- */
	Follower()
	{
	};

	void assign(string data)
	{
		this->data_ = data;
	};

	/* ---------------------------------------------------
		COMPUTATION
	--------------------------------------------------- */
	/**
	 * 무엇을 따를 지 계산함.
	 * 
	 * 왼쪽, 사선, 윗쪽의 성장 수치 중, 무엇을 따를 지 계산한다.
	 */
	int compute(int L, int D, int U)
	{
		char ch = this->data_.at(L*3*3 + D*3 + U);
		if (ch == 'L')
			return L;
		else if (ch == 'D')
			return D;
		else
			return U;
	};
};

class Element
{
private:
	int value_;
	int grow_;

	Element *L_;
	Element *D_;
	Element *U_;
	Follower follower_;

public:
	/* ---------------------------------------------------
		CONSTRUCTORS
	--------------------------------------------------- */
	Element()
	{
		this->value_ = 1;
		this->grow_ = -1;
	};

	Element(Element *L, Element *D, Element *U)
		: Element()
	{
		this->L_ = L;
		this->D_ = D;
		this->U_ = U;
	};

	void assignRule(const string &data)
	{
		this->follower_.assign(data);
	};

	/* ---------------------------------------------------
		성장치 할당
	--------------------------------------------------- */
	/**
	 * 성장 시킬 수치를 직접 할당함.
	 *
	 * 최상단 혹은 각 행의 첫번째 원소들이 사용하는 메소드.
	 */
	void reserve(int val)
	{
		this->grow_ = val;
	};

	/**
	 * 성장 시킬 수치를 추론함.
	 * 
	 * 인접한 원소들로부터 성장시킬 수치를 추론함.
	 */
	void inference()
	{
		this->grow_ = follower_.compute
		(
			this->L_->grow_,
			this->D_->grow_,
			this->U_->grow_
		);
	};

	/**
	 * 예약된 성장수치를 적용 -> 실제로 성장시킴.
	 */
	void grow()
	{
		this->value_ += grow_;
		grow_ = -1;
	};

	/* ---------------------------------------------------
		ACCESSORS
	--------------------------------------------------- */
	int value()
	{
		return this->value_;
	};
};

class QueenBee
{
private:
	typedef vector<vector<Element>> Matrix;
	typedef vector<Element> Row;

	Matrix matrix_;

public:
	QueenBee()
	{
		// 행렬 구성
		size_t M, N;
		cin >> M >> N;
		
		this->matrix_.reserve(M);

		for (size_t i = 0; i < M; i++)
		{
			this->matrix_.push_back(Row());
			Row &row = this->matrix_.back();

			row.reserve(M);
			for (size_t j = 0; j < M; j++)
				if (i == 0 || j == 0)
					row.push_back(Element());
				else
					row.push_back(Element(&this->matrix_[i][j-1], &this->matrix_[i-1][j-1], &this->matrix_[i-1][j]));
		}

		// 규칙 할당
		for (size_t i = 1; i < M; i++)
			for (size_t j = 1; j < M; j++)
			{
				string rule;
				cin >> rule;

				this->matrix_[i][j].assignRule(rule);
			}

		// 성장 데이터 입력
		for (size_t n = 0; n < N; n++)
		{
			size_t zero, one, two;
			cin >> zero >> one >> two;

			this->grow(zero, one, two);
		}

		// 결과 출력
		this->print();
	};

private:
	void grow(size_t zero, size_t one, size_t two)
	{
		// 최상단 행과, 각 행의 첫번째 열에 성장 수치를 할당
		vector<int> grow_array;
		grow_array.insert(grow_array.end(), zero, 0);
		grow_array.insert(grow_array.end(), one, 1);
		grow_array.insert(grow_array.end(), two, 2);

		size_t x = 0;
		for (size_t i = this->matrix_.size() - 1; i > 0; i--)
			this->matrix_[i][0].reserve(grow_array[x++]);
		for (size_t i = 0; i < this->matrix_.size(); i++)
			this->matrix_[0][i].reserve(grow_array[x++]);

		// 나머지 행에서 각자 성장시킬 수치를 추론한다.
		for (size_t i = 1; i < this->matrix_.size(); i++)
			for (size_t j = 1; j < this->matrix_.size(); j++)
				this->matrix_[i][j].inference();

		// 할당된 성장 수치만큼 모두 성장시킴
		for (size_t i = 0; i < this->matrix_.size(); i++)
			for (size_t j = 0; j < this->matrix_.size(); j++)
				this->matrix_[i][j].grow();
	};

	void print()
	{
		for (size_t i = 0; i < this->matrix_.size(); i++)
		{
			for (size_t j = 0; j < this->matrix_.size(); j++)
				cout << this->matrix_[i][j].value() << " ";
			cout << endl;
		}
	};
};

int main()
{
	QueenBee qb;
	return 0;
}