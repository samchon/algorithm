#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif
#ifndef INT_MIN
#	define INT_MIN (INT_MAX+1)
#endif

class Station;
class MoveHistory;

/**
 * 이동내역 클래스.
 *
 * 방문한 역(Station)과 소요시간 정보를 담음.
 */
class MoveHistory
	: public vector<Station*>
{
	friend class Station;

private:
	/**
	 * 각 역으로 이동하는 데 소요된 최소 시간을 기록한 전역 맵
	 */
	static unordered_map<Station*, int> minHoursMap;

	/**
	 * 현재 이동내역이 소모한 시간
	 */
	int hours;

public:
	/**
	 * 기본 생성자.
	 *
	 * hours를 INT_MAX로 둠. 최소값 도출절차의 초기값 구성에 사용.
	 */
	MoveHistory();

	/**
	 * 생성자 from 출발지점
	 *
	 * @param start 출발역
	 */
	MoveHistory(Station*);
	
	/**
	 * 특정 역으로 이동하며, 내역과 소요시간 또한 기록함.
	 *
	 * 현재 이동하려는 역이 과거에 다른 MoveHistory가 이미 거쳐간 역이며, 과거의 소요시간이
	 * 현재의 소요시간보다 더 짧을 때, 현재의 이동을 무의미한 것으로 봐 false를 리턴한다.
	 *
	 * @return 특정 역으로의 이동이 무의미한 경우 false
	 */
	bool moveTo(Station*);

	/**
	 * 결과 출력
	 */
	void print() const;
};

/**
 * 지하철 역 클래스.
 *
 * 역의 번호와 인접 역 및 해당 역까지의 이동시 소요시간을 담음.
 */
class Station
{
	friend class MoveHistory;

public:
	/**
	 * 현재 역의 번호.
	 */
	int no;

	/**
	 * 이웃한 역과 이동하는 데 소요되는 시간을 기록한 맵
	 */
	unordered_map<Station*, int> hoursMap;

public:
	Station(int);

	/**
	 * 이웃한 역과 이동 소요시간을 설정함.
	 */
	void setNeighbor(Station*, int);

	/**
	 * 특정 역으로 이동할 때, 가장 짧은 시간이 소요되는 이동경로를 구함.
	 *
	 * @param destination 목표 역
	 *
	 * @return 이동 내역 및 소요시간
	 */
	MoveHistory moveTo(Station*) const;

private:
	/**
	 * 특정 역으로 이동, 백그라운드 메소드.
	 * 과거의 이동내역에 더하여 특정 역으로 이동할 수 있는 가장 짧은 경로를 찾는다.
	 *
	 * @param destination 목표 역
	 * @param moveHistory 이전까지의 이동내역
	 *
	 * @return 이동 내역 및 소요시간
	 */
	MoveHistory moveTo(Station*, const MoveHistory &) const;
};

/* ---------------------------------------------------------
	MAIN
--------------------------------------------------------- */
int main()
{
	size_t n, destIndex;
	vector<Station> stationArray;

	// Station 생성
	cin >> n >> destIndex;
	for (int i = 0; i < n; i++)
	{
		stationArray.push_back(Station(i + 1));
	}

	// 각 Station 간 소요시간 설정
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
		{
			int hours;
			cin >> hours;

			// i->j 이동 시간이 j->i 의 이동시간과 다른 경우가 있다.
			if (i != j)
				stationArray[i].setNeighbor(&stationArray[j], hours);
		}

	// 최소 소요시간 이동내역 도출
	Station &start = stationArray[0];
	Station &dest = stationArray[destIndex];

	// 계산
	const MoveHistory &moveHistory = start.moveTo(&dest);

	// 최소 소요시간 일정 출력
	moveHistory.print();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}

/* ---------------------------------------------------------
	STATION
--------------------------------------------------------- */
Station::Station(int no)
{
	this->no = no;
}
void Station::setNeighbor(Station *station, int hours)
{
	hoursMap[station] = hours;
}

MoveHistory Station::moveTo(Station *destination) const
{
	MoveHistory minHistory; // 초기셋, INT_MAX

	for (auto it = hoursMap.begin(); it != hoursMap.end(); it++) //모든 이웃한 역에 대하여
	{
		Station *neighbor = it->first;

		MoveHistory myHistory((Station*)this);

		// 해당 역으로의 이동이 유의미한지 검사
		if (myHistory.moveTo(neighbor) == false) 
			continue;

		// 유의미하다면 이동을 실시
		myHistory = neighbor->moveTo(destination, myHistory);

		// 현재의 이동내역 소요시간이 최소인가?
		if (myHistory.hours < minHistory.hours)
			minHistory = myHistory;
	}

	return minHistory;
}
MoveHistory Station::moveTo(Station *destination, const MoveHistory &moveHistory) const
{
	// 목적지까지 도달함
	if (this == destination)
		return moveHistory;

	MoveHistory minHistory; // 초기셋, INT_MAX

	for (auto it = hoursMap.begin(); it != hoursMap.end(); it++) //모든 이웃한 역에 대하여
	{
		Station *neighbor = it->first;

		MoveHistory myHistory = moveHistory;

		// 해당 역으로의 이동이 유의미한지 검사
		if (myHistory.moveTo(neighbor) == false)
			continue;

		// 유의미하다면 이동을 실시
		myHistory = neighbor->moveTo(destination, myHistory);

		// 현재의 이동내역 소요시간이 최소인가?
		if (myHistory.hours < minHistory.hours)
			minHistory = myHistory;
	}

	return minHistory;
}

/* ---------------------------------------------------------
	MOVE_HISTORY_ARRAY
--------------------------------------------------------- */
unordered_map<Station*, int> MoveHistory::minHoursMap;

MoveHistory::MoveHistory()
	: vector<Station*>()
{
	// 최소값 산출을 위한 초기값 INT_MAX
	hours = INT_MAX;
}
MoveHistory::MoveHistory(Station *start)
	: vector<Station*>()
{
	// 출발 역과 소요시간 0로 초기화함
	hours = 0;
	push_back(start);
}

bool MoveHistory::moveTo(Station *destination)
{
	// 이동에 따른 추가 소요시간 계산
	hours += back()->hoursMap[destination];

	if (at(0) == destination) // 첫번째 지점으로 돌아왔거나
		return false;

	auto it = minHoursMap.find(destination);
	if (it != minHoursMap.end() && it->second < hours)
	{
		// 현재 방문하려는 지점이 과거 누군가가 방문했던 지점이며
		// 그 때 소요된 시간보다 더 많은 시간을 소요해서 도착했을 시에는
		// 실패로 간주
		return false;
	}
	else
	{
		// 현 지점에 대해 최소 소요시간으로 등록을 하고
		if (it == minHoursMap.end())
			minHoursMap[destination] = hours;
		else
			it->second = hours;

		push_back(destination); // 이동내역을 기록에 남김

		return true;
	}
}

void MoveHistory::print() const
{
	cout << hours << endl;

	for (size_t i = 0; i < size(); i++)
		cout << at(i)->no << " ";
}