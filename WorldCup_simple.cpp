/* -----------------------------------------------------------------------
이전 과정:
	6개의 팀이 각기 5번의 경기를 하니 총 경기수는 15번
	중복순열을 이용, 3^15개의 경우의 수를 통해
	가능한 모든 승,무,패의 경우의 수를 구했다

	그 결과, 경우의 수가 너무 커 시간 초과 (9초) 가 났다.

	이에 5개 팀, 각기 4번의 경기에 대하여 (총 10번의 경기) 중복순열을 이용,
	3^10개의 경우의 수를 구한 후, 이를 해쉬셋에 기록해 두었다.

	그리고 퀴즈에서 주어지는 6개 팀의 전적에 대하여, 마지막 팀과 그 전적을
	소거한 후 (각 승무패를 어느 팀과의 경기로 보냐에 따라 5!개의 경우의 수가 생김),
	이들 5개 팀의 전적에 대하여 코드를 구하여 기존의 해쉬셋에 질의, 유효성을 검증했다.
--------------------------------------------------------------------------
문제 인식:
	막상 이렇게 3^15 -> 3^10 경우의 수를 줄이기 위한 소거법을 사용해보니
	처음부터 소거법을 쓰면 되었다는 것을 알게 되었다.
--------------------------------------------------------------------------
해결책:
	퀴즈로부터 주어지는 6개 팀의 전적을, 최후의 1개 팀이 남을 때까지 계속 소거한다.
	마지막 단 한 개의 팀이 남았을 때, 단 한 번의 경기기록도 없으면 
	(승, 무, 패가 모두 0) 유효한 것으로 간주한다.

	매번 소거시마다, 소거되는 팀의 경기 기록을 어느 팀과의 경기로 보느냐에 따라 
	N!의 경우의 수가 생긴다. 즉, 6! X 5! X 4! X 3! X 2! 의 연산이 필요한 셈이다.
--------------------------------------------------------------------------
결과: 
	성공 - 0.1초, 알고리즘은 간단해졌으되 실행시간은 더 늘어났다.
	아무래도 3^10 X 6! 보다 6! X 5! X 4! X 3! X 2! 가 더 큰 수인가 보다.
----------------------------------------------------------------------- */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/* ------------------------------------------------------------
	CASE_GENERATOR
------------------------------------------------------------ */
/**
 * 경우의 수 中 N! 생성기
 */
class FactorialGenerator
{
private:
	/**
	 * 각 원소가 취할 수 있는 값의 수이자 자릿 수
	 */
	size_t n;

	/**
	 * 가능한 모든 경우의 수 개수.
	 */
	size_t size_;

	/**
	 * 1 ~ n까지 담아둔 원소 배열. 
	 * 복제를 위한 샘플 배열이다.
	 */
	vector<size_t> atomArray;

public:
	FactorialGenerator(size_t n)
	{
		this->n = n;

		size_ = n;
		for (size_t i = n - 1; i >= 1; i--)
			size_ *= i;

		atomArray.assign(n, 0);
		for (size_t i = 0; i < n; i++)
			atomArray[i] = i;
	};

	auto size() const -> size_t
	{
		return size_;
	};

	/**
	 * Index번째 경우의 수를 받아온다.
	 */
	auto at(size_t index) const -> vector<size_t>
	{
		// 일단 0 ~ n-1 까지 번호가 담긴 원소 배열을 만들고
		vector<size_t> atomArray = this->atomArray;
		vector<size_t> row(n, 0);

		for (size_t i = 0; i < n; i++)
		{
			size_t item = index % atomArray.size(); // index와 원소 갯수의 나머지를 받아와
			row[i] = atomArray[item]; // 그 번호대로 경우의 수를 확정함

			index = index / atomArray.size(); // 다음 과정을 위해 index를 조정
			atomArray.erase(atomArray.begin() + item); // 현재 사용한 번호 item도 없앰
		}

		return row;
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
	 * 여기서 음수가 발생하면, 해당 월드컵 전적이 유효하지 못한 것으로 간주됨.
	 */
	void erase(int game)
	{
		int &count = (game == Game::WIN) ? win : (game == Game::DRAW) ? draw : loss;
		count--;
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
private:
	typedef vector<Team> super;

	static const size_t TEAM_SIZE = 6;
	static const size_t GAME_SIZE = TEAM_SIZE - 1;

public:
	using super::super;

	/**
	 * Default Constructor.
	 *
	 * 한 회 월드컵의 전적을 입력받아 데이터를 구성한다.
	 */
	WorldCup()
		: super()
	{
		// 퀴즈로부터 각 팀의 전적을 입력받음
		this->assign(TEAM_SIZE, Team());
		for (size_t i = 0; i < size(); i++)
		{
			Team &team = this->at(i);

			cin >> team.win;
			cin >> team.draw;
			cin >> team.loss;
		}
	};

	auto isValid() const -> bool
	{
		if (size() == 1)
		{
			// 소거를 거듭한 끝에, 단 한 개의 팀만 남았다면
			const Team &team = this->front();

			// 아무런 전적도 없는 지를 검사해 그 결과대로 유효성 여부를 확정짓는다.
			return (team.win == 0 && team.draw == 0 && team.loss == 0);
		}

		// 사전 유효성 검증
		bool hasNegative =
			std::any_of // 단 하나라도
			(
				this->begin(), this->end(), // 현지 월드컵 기록의
				[](const Team &team) -> bool // 각 팀의 전적으로부터
				{
					//유효하지 못한 기록이 발견되면 (음수가 존재 in 승, 무 or 패)
					return team.isValid() == false;
				}
			);
		if (hasNegative == true)
			return false; // 바로 무효한 것으로 간주한다.

		// 각 팀의 전적에 무효한 기록이 없다면,
		// 마지막 팀과 그 경기를 소거한 월드컵을 만들어내 계속 검사해 나가야한다.
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
			WorldCup worldCup(*this);
			worldCup.pop_back();

			// 각 경우의 수로부터
			const vector<size_t> &row = caseGenerator.at(i);

			// 마지막 팀과 그 경기 기록들을 소거함
			for (size_t j = 0; j < row.size(); j++)
			{
				Team &team = worldCup[row[j]];
				int game = gameArray[j];

				// 마지막 팀이 이겼으면, 다른 팀에서는 패배를 지우고
				// 마지막 팀이 졌으면, 다른 팀에서는 승리를 지워야 하기에 X -1
				team.erase(game * -1);
			}

			// 해당 월드컵 기록이 유효하다면, 바로 유효하다 간주
			if (worldCup.isValid() == true)
				return true;
		}

		// 어느 기록도 유효하지 못했다면, 정말 유효하지 못한 거임.
		return false;
	};
};

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