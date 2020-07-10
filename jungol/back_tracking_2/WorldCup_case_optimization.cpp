/* -----------------------------------------------------------------------
문제점:
	6개의 팀이 각기 5번의 경기를 하니 총 경기수는 15번
		중복순열을 이용, 3^15개의 경우의 수를 통해
		가능한 모든 승,무,패의 경우의 수를 구했다

	그 결과, 경우의 수가 너무 커 시간 초과 (9초) 가 났다.
--------------------------------------------------------------------------
해결책: 
	5개의 팀이 각기 4번의 경기를 하면, 총 경기 수는 10번
	3^10 번의 경우의 수가 생기니, 소요 시간이 1/3^5 으로 줄어들 것이다.

	우선, 3^10 경우의 수를 모두 구하여 둔 뒤,
	퀴즈로부터 입력되는 월드컵 전적표에서, 마지막 팀을 지워버린다.

	마지막 팀이 거둔 승,무,패에 따라, 각 팀에게서 패,무,승을 소거해야 한다.
	이 때, 각 경기를 어느 팀에서 소거할 지에 대해 
		가능한 경우의 수는 5!개

	소거 가능한 5! 의 경우의 수 중에, 기존에 구해둔 3^10 개의 경우의 수와
	같은 전적이 있으면, 유효한 것으로 보고, 단 하나도 없다면, 그 때는 실패
--------------------------------------------------------------------------
결과: 성공 - 0.023초
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
 * (추상) 경우의 수 생성기.
 */
class CaseGenerator
{
protected:
	/**
	 * 각 원소가 취할 수 있는 값의 수.
	 */
	size_t n;

	/**
	 * 자릿수 R.
	 */
	size_t r;

	/**
	 * 가능한 모든 경우의 수 개수.
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
	 * index 번째 경우의 수 배열.
	 */
	virtual auto at(size_t) const -> vector<size_t> = 0;
};

/**
* 중복순열 경우의 수 생성기.
*
* 중복순열은 n^r 으로써 0 ~ (n^r - 1) 까지의 숫자를 r 자릿수의 n진수로 나타날 수 있으면 된다.
*/
class CombinedPermutationGenerator
	: public CaseGenerator
{
private:
	typedef CaseGenerator super;

	/**
	 * 0 ~ (n^r - 1) 까지의 숫자를 각기 i번째의 n진수로 만들어주기 위한 나누기 배열.
	 *
	 * n^i를 담고 있다.
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
	 * index 번째 경우의 수 배열.
	 *
	 * index를 r자리의 n진수로 표현한 것과 같다.
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
 * 순열 생성기.
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
		// 일단 0 ~ n-1 까지 번호가 담긴 원소 배열을 만들고
		vector<size_t> atomArray = this->atomArray;
		vector<size_t> row(r, 0);

		for (size_t i = 0; i < row.size(); i++)
		{
			int item = x % atomArray.size(); // index와 원소 갯수의 나머지를 받아와
			x = x / atomArray.size(); // 그 번호대로 경우의 수를 확정함

			row[i] = atomArray[item]; // 다음 과정을 위해 index를 조정
			atomArray.erase(atomArray.begin() + item); // 현재 사용한 번호 item도 없앰
		}
		return row;
	};
};

/**
 * N! 생성기.
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
 * 한 팀의 전적.
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
	 * 해당되는 게임의 카운트를 1 만큼 줄인다.
	 *
	 * 여기서 음수가 발생하면, 해당 월드컵 전적이 유효하지 못한 것으로 간주됨.
	 */
	void erase(int game)
	{
		int &count = (game == Game::WIN) ? win : (game == Game::DRAW) ? draw : loss;
		count--;
	};

	/**
	 * 현재 팀의 전적을 8진수의 UNIQUE KEY로 변환.
	 *
	 * 8진수의 숫자로써, 첫 번째 자리는 승리 횟수, 두번째 자리는 패배 횟수.
	 */
	auto toCode(unsigned long long unit) const -> unsigned long long
	{
		return win*8*unit + loss*unit;
	};

	/**
	 * 현재 팀의 전적이 유효한가.
	 *
	 * 승, 무, 패의 전적 중에 음수의 숫자가 없으면 유효한 것으로 본다.
	 */
	auto isValid() const -> bool
	{
		return win >= 0 && draw >= 0 && loss >= 0;
	};
};

/**
 * 한 회의 월드컵.
 *
 * 각 팀의 전적을 담은 Team 객체들을 보유한다.
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
	 * 발생 가능한 모든 경우의 수를 담은 해쉬셋.
	 *
	 * 발생 가능한 모든 (월드컵 전적) 경우의 수가 변환된 8진수의 unique key를 담고 있다. 
	 */
	static unordered_set<unsigned long long> codeSet;

public:
	using super::super;

	/**
	 * Deafult Constructor.
	 *
	 * 한 회 월드컵의 전적을 입력받아 데이터를 구성한다.
	 */
	WorldCup()
		: super()
	{
		if (codeSet.empty() == true)
		{
			// LAZY CONSTRUCTOR
			// 가능한 모든 전적의 경우의 수를 발생시켜
			// 이를 codeSet에 기록해둔다.

			// 6팀에 각 팀당 5 게임이 아닌, 5팀에 각 팀당 4게임의 경우의 수를 구한다.
			CombinedPermutationGenerator caseGenerator(3, (TEAM_SIZE - 1) * (GAME_SIZE - 1) / 2);

			for (size_t i = 0; i < caseGenerator.size(); i++)
			{
				// 주어진 경우의 수로부터 한 회의 월드컵을 구성하고
				WorldCup teamArray(caseGenerator.at(i));

				// 이 기록의 코드를, 코드셋에 입력한다.
				codeSet.insert(teamArray.toCode());
			}
		}

		// 퀴즈로부터 각 팀의 전적을 입력받음
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
	 * Construct from a 경우의 수.
	 *
	 * 사용자나 퀴즈가 아닌, 프로그램 내부에서만 사용되는 생성자.
	 * 각 전적의 경우의 수를 담은 index 배열을 담아 한 회의 월드컵 정보를 구성함.
	 *
	 * @param row 경우의 수 index 배열
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
	 * 현재 월드컵의 전적을 8진수의 UNIQUE KEY로 변환.
	 *
	 * 각 팀당 2자리씩 차지한다. 8진수 10자리 (5팀 x 2).
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
	 * 현재 월드컵의 전적이 유효한가.
	 *
	 * 마지막 팀을 소거한 후 (6개 팀 -> 5개 팀), 마지막 팀과의 경기 결과 역시 모두 취소한다.
	 * 그렇게 남은 5개의 팀의 전적 코드가 codeSet에 등록된, 가능한 모든 전적의 경우의 수, 
	 * 코드에 존재하는 지를 검사한다.
	 *
	 * @return 현재 월드컵 전적의 유효성 여부
	 */
	auto isValid() const -> bool
	{
		// 마지막 팀과 그 경기를 소거한 월드컵을 만들어내야 한다.
		const Team &lastTeam = this->back();
		vector<int> gameArray;

		// 게임 기록을 기록해놓음
		gameArray.insert(gameArray.end(), (size_t)lastTeam.win, Game::WIN); 
			// 마지막 팀의 승리 횟수만큼, Game::WIN을 gameArray에 입력한다는 의미이다.
		gameArray.insert(gameArray.end(), (size_t)lastTeam.draw, Game::DRAW);
		gameArray.insert(gameArray.end(), (size_t)lastTeam.loss, Game::LOSS);

		// 각 팀으로부터 마지막 팀과의 경기 기록을 소거해야 하는데
		// 어느 경기를 어느 팀으로부터 소거할 지, 총 N! 개의 경우의 수가 생긴다
		FactorialGenerator caseGenerator(gameArray.size());
		for (size_t i = 0; i < caseGenerator.size(); i++)
		{
			// 마지막 팀이 없는 가상의 월드컵 기록을 만든 후
			WorldCup worldCup(this->begin(), this->begin() + (TEAM_SIZE - 1));

			// 각 경우의 수로부터
			const vector<size_t> &row = caseGenerator.at(i);

			// 마지막 팀과의 그 경기 기록을 소거함
			for (size_t j = 0; j < row.size(); j++)
			{
				Team &team = worldCup[row[j]];
				int game = gameArray[j];

				// 마지막 팀이 이겼으면, 다른 팀에서는 패배를 지우고
				// 마지막 팀이 졌으면, 다른 팀에서는 승리를 지워야 하기에 X -1
				team.erase(game * -1);
			}
			
			// 각 팀에 음수의 전적이 존재하는 지 검사하여
			// 음수의 전적이 존재하면 무효한 것으로 간주
			bool partialValidity = true;
			for (size_t j = 0; j < worldCup.size(); j++)
				if (worldCup[j].isValid() == false)
				{
					partialValidity = false;

					break;
				}

			if (partialValidity == true)
			{
				// 각 경우의 수로부터 소거된 월드컵이
				unsigned long long code = worldCup.toCode();

				// 사전에 등록된 모든 경우의 수의 코드셋에 등록된 것이면, TRUE
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