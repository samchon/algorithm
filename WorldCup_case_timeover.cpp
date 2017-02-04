/* --------------------------------------------------------
풀이법:
	6개의 팀이 각기 5번의 경기를 하니 총 경기수는 15번
		중복순열을 이용, 3^15개의 경우의 수를 통해
		가능한 모든 승,무,패의 경우의 수를 구하고
		
	퀴즈로 입력되는 월드컵 전적표가
		미리 구해놓은 모든 경우의 수에 들어있는 지를 확인
-----------------------------------------------------------
결과: 시간 초과 - 9초 걸림
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
 * 중복순열 경우의 수 생성기.
 *
 * 중복순열은 n^r 으로써 0 ~ (n^r - 1) 까지의 숫자를 r 자릿수의 n진수로 나타날 수 있으면 된다.
 */
class CombinedPermutationGenerator
{
private:
	/**
	 * 각 원소가 취할 수 있는 값의 수.
	 */
	size_t n;

	/**
	 * 자릿수 R.
	 */
	size_t r;

	/**
	 * 경우의 수, n^r개.
	 */
	size_t size_;

	/**
	 * 0 ~ (n^r - 1) 까지의 숫자를 각기 i번째의 n진수로 만들어주기 위한 나누기 배열.
	 *
	 * n^i를 담고 있다.
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
	 * index 번째 경우의 수 배열.
	 *
	 * index를 r자리의 n진수로 표현한 것과 같다.
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
 * 한 팀의 전적.
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
	 * 현재 팀의 전적을 8진수의 UNIQUE KEY로 변환.
	 *
	 * 8진수의 숫자로써, 첫 번째 자리는 승리 횟수, 두번째 자리는 패배 횟수.
	 */
	auto toCode(unsigned long long unit) const -> unsigned long long
	{
		return win*unit*8 + loss*unit;
	}
};

/**
 * 한 회의 월드컵.
 *
 * 각 팀의 전적을 담은 Team 객체들을 보유한다.
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
	 * 발생 가능한 모든 경우의 수를 담은 해쉬셋.
	 *
	 * 발생 가능한 모든 (월드컵 전적) 경우의 수가 변환된 8진수의 unique key를 담고 있다. 
	 */
	static SET<unsigned long long> codeSet;

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
			CombinedPermutationGenerator caseGenerator(3, TEAM_SIZE * GAME_SIZE / 2);

			codeSet.reserve(caseGenerator.size());

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
	 * 현재 팀의 전적을 8진수의 UNIQUE KEY로 변환.
	 *
	 * 8진수의 숫자로써, 첫 번째 자리는 승리 횟수, 두번째 자리는 패배 횟수.
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
	 * 현재 월드컵의 전적이 유효한가.
	 *
	 * 현재 월드컵의 UNIQUE KEY가, codeSet, 
	 * 가능한 모든 전적의 경우의 수 해쉬셋, 에 등록되어있는 지를 검사한다.
	 *
	 * @return 현재 월드컵 전적의 유효성 여부
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