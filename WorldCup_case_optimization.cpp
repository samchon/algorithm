/* -----------------------------------------------------------------------
������:
	6���� ���� ���� 5���� ��⸦ �ϴ� �� ������ 15��
		�ߺ������� �̿�, 3^15���� ����� ���� ����
		������ ��� ��,��,���� ����� ���� ���ߴ�

	�� ���, ����� ���� �ʹ� Ŀ �ð� �ʰ� (9��) �� ����.
--------------------------------------------------------------------------
�ذ�å: 
	5���� ���� ���� 4���� ��⸦ �ϸ�, �� ��� ���� 10��
	3^10 ���� ����� ���� �����, �ҿ� �ð��� 1/3^5 ���� �پ�� ���̴�.

	�켱, 3^10 ����� ���� ��� ���Ͽ� �� ��,
	����κ��� �ԷµǴ� ������ ����ǥ����, ������ ���� ����������.

	������ ���� �ŵ� ��,��,�п� ����, �� �����Լ� ��,��,���� �Ұ��ؾ� �Ѵ�.
	�� ��, �� ��⸦ ��� ������ �Ұ��� ���� ���� 
		������ ����� ���� 5!��

	�Ұ� ������ 5! �� ����� �� �߿�, ������ ���ص� 3^10 ���� ����� ����
	���� ������ ������, ��ȿ�� ������ ����, �� �ϳ��� ���ٸ�, �� ���� ����
--------------------------------------------------------------------------
���: ���� - 0.023��
----------------------------------------------------------------------- */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

/* ------------------------------------------------------------
	CASE_GENERATOR
------------------------------------------------------------ */
/**
 * (�߻�) ����� �� ������.
 */
class CaseGenerator
{
protected:
	/**
	 * �� ���Ұ� ���� �� �ִ� ���� ��.
	 */
	size_t n;

	/**
	 * �ڸ��� R.
	 */
	size_t r;

	/**
	 * ������ ��� ����� �� ����.
	 */
	size_t size_;

public:
	CaseGenerator(size_t n, size_t r)
	{
		this->n = n;
		this->r = r;
	};

	auto size() const -> size_t
	{
		return size_;
	}

	/**
	 * index ��° ����� �� �迭.
	 */
	virtual auto at(size_t) const -> vector<size_t> = 0;
};

/**
* �ߺ����� ����� �� ������.
*
* �ߺ������� n^r ���ν� 0 ~ (n^r - 1) ������ ���ڸ� r �ڸ����� n������ ��Ÿ�� �� ������ �ȴ�.
*/
class CombinedPermutationGenerator
	: public CaseGenerator
{
private:
	typedef CaseGenerator super;

	/**
	 * 0 ~ (n^r - 1) ������ ���ڸ� ���� i��°�� n������ ������ֱ� ���� ������ �迭.
	 *
	 * n^i�� ��� �ִ�.
	 */
	vector<size_t> dividerArray;

public:
	CombinedPermutationGenerator(size_t n, size_t r)
		: super(n, r)
	{
		this->size_ = pow(n, r);
		this->dividerArray.assign(r, 0);

		for (size_t i = 0; i < r; i++)
		{
			size_t x = r - (i + 1);
			dividerArray[i] = (size_t)pow(n, x);
		}
	};

	/**
	 * index ��° ����� �� �迭.
	 *
	 * index�� r�ڸ��� n������ ǥ���� �Ͱ� ����.
	 */
	virtual auto at(size_t index) const -> vector<size_t> override
	{
		vector<size_t> row(r, 0);

		for (size_t i = 0; i < row.size(); i++)
			row[i] = (index / dividerArray[i]) % n;

		return row;
	};
};

/**
 * ���� ������.
 */
class PermutationGenerator
	: public CaseGenerator
{
private:
	typedef CaseGenerator super;

	vector<size_t> atomArray;

public:
	PermutationGenerator(size_t n, size_t r)
		: super(n, r)
	{
		size_ = n;
		for (size_t i = n - 1; i > n - r; i--)
			size_ *= i;

		atomArray.assign(n, 0);
		for (size_t i = 0; i < n; i++)
			atomArray[i] = i;
	};

	virtual auto at(size_t x) const -> vector<size_t> override
	{
		// �ϴ� 0 ~ n-1 ���� ��ȣ�� ��� ���� �迭�� �����
		vector<size_t> atomArray = this->atomArray;
		vector<size_t> row(r, 0);

		for (size_t i = 0; i < row.size(); i++)
		{
			int item = x % atomArray.size(); // index�� ���� ������ �������� �޾ƿ�
			x = x / atomArray.size(); // �� ��ȣ��� ����� ���� Ȯ����

			row[i] = atomArray[item]; // ���� ������ ���� index�� ����
			atomArray.erase(atomArray.begin() + item); // ���� ����� ��ȣ item�� ����
		}
		return row;
	};
};

/**
 * N! ������.
 */
class FactorialGenerator
	: public PermutationGenerator
{
private:
	typedef PermutationGenerator super;

public:
	FactorialGenerator(size_t n)
		: super(n, n)
	{
	};
};

/* ------------------------------------------------------------
	WORLD_CUP
------------------------------------------------------------ */
enum Game : int
{
	WIN = 1,
	DRAW = 0,
	LOSS = -1
};

class WorldCup;
class Team;

/**
 * �� ���� ����.
 */
class Team
{
	friend class WorldCup;

private:
	int win;
	int draw;
	int loss;

public:
	Team()
	{
		win = 0;
		draw = 0;
		loss = 0;
	};

private:
	/**
	 * �ش�Ǵ� ������ ī��Ʈ�� 1 ��ŭ ���δ�.
	 *
	 * ���⼭ ������ �߻��ϸ�, �ش� ������ ������ ��ȿ���� ���� ������ ���ֵ�.
	 */
	void erase(int game)
	{
		int &count = (game == Game::WIN) ? win : (game == Game::DRAW) ? draw : loss;
		count--;
	};

	/**
	 * ���� ���� ������ 8������ UNIQUE KEY�� ��ȯ.
	 *
	 * 8������ ���ڷν�, ù ��° �ڸ��� �¸� Ƚ��, �ι�° �ڸ��� �й� Ƚ��.
	 */
	auto toCode(unsigned long long unit) const -> unsigned long long
	{
		return win*8*unit + loss*unit;
	};

	/**
	 * ���� ���� ������ ��ȿ�Ѱ�.
	 *
	 * ��, ��, ���� ���� �߿� ������ ���ڰ� ������ ��ȿ�� ������ ����.
	 */
	auto isValid() const -> bool
	{
		return win >= 0 && draw >= 0 && loss >= 0;
	};
};

/**
 * �� ȸ�� ������.
 *
 * �� ���� ������ ���� Team ��ü���� �����Ѵ�.
 */
class WorldCup
	: public vector<Team>
{
public:
	static const size_t TEAM_SIZE = 6;
	static const size_t GAME_SIZE = TEAM_SIZE - 1;

private:
	typedef vector<Team> super;

	/**
	 * �߻� ������ ��� ����� ���� ���� �ؽ���.
	 *
	 * �߻� ������ ��� (������ ����) ����� ���� ��ȯ�� 8������ unique key�� ��� �ִ�. 
	 */
	static unordered_set<unsigned long long> codeSet;

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

			// 6���� �� ���� 5 ������ �ƴ�, 5���� �� ���� 4������ ����� ���� ���Ѵ�.
			CombinedPermutationGenerator caseGenerator(3, (TEAM_SIZE - 1) * (GAME_SIZE - 1) / 2);

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
		this->assign(TEAM_SIZE - 1, Team());
		int k = 0;

		for (size_t i = 0; i < size(); i++)
			for (size_t j = i + 1; j < size(); j++)
			{
				int game = row[k++];

				if (game == Game::WIN)
				{
					at(i).win++;
					at(j).loss++;
				}
				else if (game == Game::LOSS)
				{
					at(i).draw++;
					at(j).draw++;
				}
				else if (game == Game::DRAW)
				{
					at(i).loss++;
					at(j).win++;
				}
			}
	};

	/**
	 * ���� �������� ������ 8������ UNIQUE KEY�� ��ȯ.
	 *
	 * �� ���� 2�ڸ��� �����Ѵ�. 8���� 10�ڸ� (5�� x 2).
	 */
	auto toCode() const -> unsigned long long
	{
		unsigned long long code = 0;
		unsigned long long unit = 1;

		for (size_t i = 0; i < size(); i++)
		{
			code += this->at(i).toCode(unit);
			unit *= 64;
		}
		return code;
	};

public:
	/**
	 * ���� �������� ������ ��ȿ�Ѱ�.
	 *
	 * ������ ���� �Ұ��� �� (6�� �� -> 5�� ��), ������ ������ ��� ��� ���� ��� ����Ѵ�.
	 * �׷��� ���� 5���� ���� ���� �ڵ尡 codeSet�� ��ϵ�, ������ ��� ������ ����� ��, 
	 * �ڵ忡 �����ϴ� ���� �˻��Ѵ�.
	 *
	 * @return ���� ������ ������ ��ȿ�� ����
	 */
	auto isValid() const -> bool
	{
		// ������ ���� �� ��⸦ �Ұ��� �������� ������ �Ѵ�.
		const Team &lastTeam = this->back();
		vector<int> gameArray;

		// ���� ����� ����س���
		gameArray.insert(gameArray.end(), (size_t)lastTeam.win, Game::WIN); 
			// ������ ���� �¸� Ƚ����ŭ, Game::WIN�� gameArray�� �Է��Ѵٴ� �ǹ��̴�.
		gameArray.insert(gameArray.end(), (size_t)lastTeam.draw, Game::DRAW);
		gameArray.insert(gameArray.end(), (size_t)lastTeam.loss, Game::LOSS);

		// �� �����κ��� ������ ������ ��� ����� �Ұ��ؾ� �ϴµ�
		// ��� ��⸦ ��� �����κ��� �Ұ��� ��, �� N! ���� ����� ���� �����
		FactorialGenerator caseGenerator(gameArray.size());
		for (size_t i = 0; i < caseGenerator.size(); i++)
		{
			// ������ ���� ���� ������ ������ ����� ���� ��
			WorldCup worldCup(this->begin(), this->begin() + (TEAM_SIZE - 1));

			// �� ����� ���κ���
			const vector<size_t> &row = caseGenerator.at(i);

			// ������ ������ �� ��� ����� �Ұ���
			for (size_t j = 0; j < row.size(); j++)
			{
				Team &team = worldCup[row[j]];
				int game = gameArray[j];

				// ������ ���� �̰�����, �ٸ� �������� �й踦 �����
				// ������ ���� ������, �ٸ� �������� �¸��� ������ �ϱ⿡ X -1
				team.erase(game * -1);
			}
			
			// �� ���� ������ ������ �����ϴ� �� �˻��Ͽ�
			// ������ ������ �����ϸ� ��ȿ�� ������ ����
			bool partialValidity = true;
			for (size_t j = 0; j < worldCup.size(); j++)
				if (worldCup[j].isValid() == false)
				{
					partialValidity = false;

					break;
				}

			if (partialValidity == true)
			{
				// �� ����� ���κ��� �Ұŵ� ��������
				unsigned long long code = worldCup.toCode();

				// ������ ��ϵ� ��� ����� ���� �ڵ�¿� ��ϵ� ���̸�, TRUE
				if (codeSet.count(code) != 0)
					return true;
			}
		}

		return false;
	};
};
unordered_set<unsigned long long> WorldCup::codeSet;

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