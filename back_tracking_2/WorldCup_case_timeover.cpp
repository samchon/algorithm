/* --------------------------------------------------------
Ǯ�̹�:
	6���� ���� ���� 5���� ��⸦ �ϴ� �� ������ 15��
		�ߺ������� �̿�, 3^15���� ����� ���� ����
		������ ��� ��,��,���� ����� ���� ���ϰ�
		
	����� �ԷµǴ� ������ ����ǥ��
		�̸� ���س��� ��� ����� ���� ����ִ� ���� Ȯ��
-----------------------------------------------------------
���: �ð� �ʰ� - 9�� �ɸ�
-------------------------------------------------------- */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <chrono>

using namespace std;

#define SET unordered_set

/* ------------------------------------------------------------
	CASE_GENERATOR
------------------------------------------------------------ */
/**
 * �ߺ����� ����� �� ������.
 *
 * �ߺ������� n^r ���ν� 0 ~ (n^r - 1) ������ ���ڸ� r �ڸ����� n������ ��Ÿ�� �� ������ �ȴ�.
 */
class CombinedPermutationGenerator
{
private:
	/**
	 * �� ���Ұ� ���� �� �ִ� ���� ��.
	 */
	size_t n;

	/**
	 * �ڸ��� R.
	 */
	size_t r;

	/**
	 * ����� ��, n^r��.
	 */
	size_t size_;

	/**
	 * 0 ~ (n^r - 1) ������ ���ڸ� ���� i��°�� n������ ������ֱ� ���� ������ �迭.
	 *
	 * n^i�� ��� �ִ�.
	 */
	vector<size_t> dividerArray;

public:
	CombinedPermutationGenerator(size_t n, size_t r)
	{
		this->n = n;
		this->r = r;

		this->size_ = pow(n, r);
		this->dividerArray.assign(r, 0);

		for (size_t i = 0; i < r; i++)
		{
			size_t x = r - (i + 1);
			dividerArray[i] = (size_t)pow(n, x);
		}
	};

	size_t size() const
	{
		return size_;
	}

	/**
	 * index ��° ����� �� �迭.
	 *
	 * index�� r�ڸ��� n������ ǥ���� �Ͱ� ����.
	 */
	vector<size_t> at(size_t index) const
	{
		vector<size_t> row(r, 0);

		for (size_t i = 0; i < row.size(); i++)
			row[i] = (index / dividerArray[i]) % n;

		return row;
	};
};

/* ------------------------------------------------------------
	WORLD_CUP
------------------------------------------------------------ */
class WorldCup;

/**
 * �� ���� ����.
 */
class Team
{
	friend class WorldCup;

private:
	size_t win;
	size_t draw;
	size_t loss;

public:
	Team()
	{
		win = 0;
		draw = 0;
		loss = 0;
	};

private:
	/**
	 * ���� ���� ������ 8������ UNIQUE KEY�� ��ȯ.
	 *
	 * 8������ ���ڷν�, ù ��° �ڸ��� �¸� Ƚ��, �ι�° �ڸ��� �й� Ƚ��.
	 */
	auto toCode(unsigned long long unit) const -> unsigned long long
	{
		return win*unit*8 + loss*unit;
	}
};

/**
 * �� ȸ�� ������.
 *
 * �� ���� ������ ���� Team ��ü���� �����Ѵ�.
 */
class WorldCup
	: public vector<Team>
{
private:
	typedef vector<Team> super;

	static const size_t TEAM_SIZE = 6;
	static const size_t GAME_SIZE = TEAM_SIZE - 1;

	static const size_t WIN = 1;
	static const size_t DRAW = 0;
	static const size_t LOSS = 2;

	/**
	 * �߻� ������ ��� ����� ���� ���� �ؽ���.
	 *
	 * �߻� ������ ��� (������ ����) ����� ���� ��ȯ�� 8������ unique key�� ��� �ִ�. 
	 */
	static SET<unsigned long long> codeSet;

public:
	using super::super;

	/**
	 * Deafult Constructor.
	 *
	 * �� ȸ �������� ������ �Է¹޾� �����͸� �����Ѵ�.
	 */
	WorldCup()
		: super()
	{
		if (codeSet.empty() == true)
		{
			// LAZY CONSTRUCTOR
			// ������ ��� ������ ����� ���� �߻�����
			// �̸� codeSet�� ����صд�.
			CombinedPermutationGenerator caseGenerator(3, TEAM_SIZE * GAME_SIZE / 2);

			codeSet.reserve(caseGenerator.size());

			for (size_t i = 0; i < caseGenerator.size(); i++)
			{
				// �־��� ����� ���κ��� �� ȸ�� �������� �����ϰ�
				WorldCup teamArray(caseGenerator.at(i));

				// �� ����� �ڵ带, �ڵ�¿� �Է��Ѵ�.
				codeSet.insert(teamArray.toCode());
			}
		}

		// ����κ��� �� ���� ������ �Է¹���
		this->assign(TEAM_SIZE, Team());
		for (size_t i = 0; i < size(); i++)
		{
			Team &team = this->at(i);

			cin >> team.win;
			cin >> team.draw;
			cin >> team.loss;
		}
	}

private:
	/**
	 * Construct from a ����� ��.
	 *
	 * ����ڳ� ��� �ƴ�, ���α׷� ���ο����� ���Ǵ� ������.
	 * �� ������ ����� ���� ���� index �迭�� ��� �� ȸ�� ������ ������ ������.
	 *
	 * @param row ����� �� index �迭
	 */
	WorldCup(const vector<size_t> &row)
		: super()
	{
		this->assign(6, Team());
		size_t k = 0;

		for (size_t i = 0; i < size(); i++)
			for (size_t j = i + 1; j < size(); j++)
			{
				size_t game = row[k++];

				if (game == WIN)
				{
					at(i).win++;
					at(j).loss++;
				}
				else if (game == LOSS)
				{
					at(i).draw++;
					at(j).draw++;
				}
				else if (game == DRAW)
				{
					at(i).loss++;
					at(j).win++;
				}
			}
	};

	/**
	 * ���� ���� ������ 8������ UNIQUE KEY�� ��ȯ.
	 *
	 * 8������ ���ڷν�, ù ��° �ڸ��� �¸� Ƚ��, �ι�° �ڸ��� �й� Ƚ��.
	 */
	auto toCode() const -> unsigned long long
	{
		unsigned long long code = 0;
		unsigned long long unit = 1;

		for (size_t i = 0; i < size(); i++)
		{
			code += at(i).toCode(unit);
			unit *= 64;
		}

		return code;
	};

public:
	/**
	 * ���� �������� ������ ��ȿ�Ѱ�.
	 *
	 * ���� �������� UNIQUE KEY��, codeSet, 
	 * ������ ��� ������ ����� �� �ؽ���, �� ��ϵǾ��ִ� ���� �˻��Ѵ�.
	 *
	 * @return ���� ������ ������ ��ȿ�� ����
	 */
	auto isValid() const -> bool
	{
		return codeSet.count(toCode()) != 0;
	};
};
SET<unsigned long long> WorldCup::codeSet;

int main()
{
	for (size_t i = 0; i < 4; i++)
	{
		WorldCup worldCup;

		cout << worldCup.isValid() << " ";
	}

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}