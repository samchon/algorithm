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
	 * ������ ���� �� �����.
	 * 
	 * ����, �缱, ������ ���� ��ġ ��, ������ ���� �� ����Ѵ�.
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
		����ġ �Ҵ�
	--------------------------------------------------- */
	/**
	 * ���� ��ų ��ġ�� ���� �Ҵ���.
	 *
	 * �ֻ�� Ȥ�� �� ���� ù��° ���ҵ��� ����ϴ� �޼ҵ�.
	 */
	void reserve(int val)
	{
		this->grow_ = val;
	};

	/**
	 * ���� ��ų ��ġ�� �߷���.
	 * 
	 * ������ ���ҵ�κ��� �����ų ��ġ�� �߷���.
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
	 * ����� �����ġ�� ���� -> ������ �����Ŵ.
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
		// ��� ����
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

		// ��Ģ �Ҵ�
		for (size_t i = 1; i < M; i++)
			for (size_t j = 1; j < M; j++)
			{
				string rule;
				cin >> rule;

				this->matrix_[i][j].assignRule(rule);
			}

		// ���� ������ �Է�
		for (size_t n = 0; n < N; n++)
		{
			size_t zero, one, two;
			cin >> zero >> one >> two;

			this->grow(zero, one, two);
		}

		// ��� ���
		this->print();
	};

private:
	void grow(size_t zero, size_t one, size_t two)
	{
		// �ֻ�� ���, �� ���� ù��° ���� ���� ��ġ�� �Ҵ�
		vector<int> grow_array;
		grow_array.insert(grow_array.end(), zero, 0);
		grow_array.insert(grow_array.end(), one, 1);
		grow_array.insert(grow_array.end(), two, 2);

		size_t x = 0;
		for (size_t i = this->matrix_.size() - 1; i > 0; i--)
			this->matrix_[i][0].reserve(grow_array[x++]);
		for (size_t i = 0; i < this->matrix_.size(); i++)
			this->matrix_[0][i].reserve(grow_array[x++]);

		// ������ �࿡�� ���� �����ų ��ġ�� �߷��Ѵ�.
		for (size_t i = 1; i < this->matrix_.size(); i++)
			for (size_t j = 1; j < this->matrix_.size(); j++)
				this->matrix_[i][j].inference();

		// �Ҵ�� ���� ��ġ��ŭ ��� �����Ŵ
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