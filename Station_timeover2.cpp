#include <iostream>
#include <vector>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

class MoveHistory;
class Station;

/**
 * 전체 역 정보
 */
vector<Station> stationArray;

/**
 * 각 역으로 이동하는 데 소요된 최소 시간을 기록
 */
vector<int> minHoursArray;

/**
 * 지하철 역 클래스.
 *
 * 역의 번호와 인접 역 및 해당 역까지의 이동시 소요시간을 담음.
 */
class Station
{
	friend class MoveHistory;

private:
	/**
	 * 현재 역의 번호.
	 */
	size_t index;

	/**
	 * 이웃한 역으로 이동하는 데 소요되는 시간
	 */
	vector<int> hoursArray;

public:
	Station(size_t);

	/**
	* 이웃한 역과 이동 소요시간을 설정함.
	*/
	void setNeighbor(const Station &, int);

	/**
	* 특정 역으로 이동할 때, 가장 짧은 시간이 소요되는 이동경로를 구함.
	*
	* @param destination 목표 역
	*
	* @return 이동 내역 및 소요시간
	*/
	MoveHistory moveTo(const Station &) const;

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
	MoveHistory moveTo(const Station &, const MoveHistory &) const;
};

/**
 * 이동내역 클래스.
 *
 * 방문한 역(Station)과 소요시간 정보를 담음.
 */
class MoveHistory
	: vector<size_t>
{
	friend class Station;

private:
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
	MoveHistory(const Station &);

	/**
	* 특정 역으로 이동하며, 내역과 소요시간 또한 기록함.
	*
	* 현재 이동하려는 역이 과거에 다른 MoveHistory가 이미 거쳐간 역이며, 과거의 소요시간이
	* 현재의 소요시간보다 더 짧을 때, 현재의 이동을 무의미한 것으로 봐 false를 리턴한다.
	*
	* @return 특정 역으로의 이동이 무의미한 경우 false
	*/
	bool moveTo(const Station &);

	/**
	* 결과 출력
	*/
	void print() const;
};

/* ---------------------------------------------------------
	MAIN
--------------------------------------------------------- */
int main()
{
	//////////////////////////////
	// Station 및 소요시간 구성
	//////////////////////////////
	size_t size, destIndex;
	cin >> size >> destIndex;

	// Station 구성
	stationArray.assign(size + 1, Station(0));
	minHoursArray.assign(size + 1, INT_MAX);
	
	for (size_t i = 1; i <= size; i++)
		stationArray[i] = Station(i);

	// 소요시간 설정
	for (size_t i = 1; i <= size; i++)
		for (size_t j = 1; j <= size; j++)
		{
			int hours;
			cin >> hours;

			stationArray[i].setNeighbor(stationArray[j], hours);
		}

	//////////////////////////////
	// 최소 소요시간 도출
	//////////////////////////////
	const Station &start = stationArray[1];
	const Station &dest = stationArray[destIndex];

	// 계산
	const MoveHistory &moveHistory = start.moveTo(dest);

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
Station::Station(size_t index)
{
	this->index = index;
	hoursArray.assign(stationArray.size(), INT_MAX);
}
void Station::setNeighbor(const Station &station, int hours)
{
	hoursArray[station.index] = hours;
}

MoveHistory Station::moveTo(const Station &dest) const
{
	MoveHistory minHistory; // 초기셋, INT_MAX

	for (size_t i = 1; i < hoursArray.size(); i++)
	{
		// 자기 자신에게로 이동하지는 않음
		if (i == this->index)
			continue;

		MoveHistory myHistory(*this); // 이동 내역
		const Station &next = stationArray[i]; // 다음으로 이동할 역

		// 해당 역으로의 이동이 유의미한지 검사
		if (myHistory.moveTo(next) == false)
			continue;

		// 유의미하다면 이동을 실시
		myHistory = next.moveTo(dest, myHistory);

		// 현재의 이동내역 소요시간이 최소인가?
		if (myHistory.hours < minHistory.hours)
			minHistory = myHistory;
	}

	return minHistory;
}
MoveHistory Station::moveTo(const Station &dest, const MoveHistory &moveHistory) const
{
	if (this == &dest)
		return moveHistory;

	MoveHistory minHistory; // 초기셋, INT_MAX

	for (size_t i = 1; i < hoursArray.size(); i++)
	{
		// 자기 자신에게로 이동하지는 않음
		if (i == this->index)
			continue;

		MoveHistory myHistory = moveHistory;
		const Station &next = stationArray[i]; // 다음으로 이동할 역

		if (myHistory.moveTo(next) == false) // 해당 역으로의 이동이 유의미한지 검사
			continue;

		// 유의미하다면 이동을 실시
		myHistory = next.moveTo(dest, myHistory);

		// 현재의 이동내역 소요시간이 최소인가?
		if (myHistory.hours < minHistory.hours)
			minHistory = myHistory;
	}

	return minHistory;
}

/* ---------------------------------------------------------
	MOVE_HISTORY
--------------------------------------------------------- */
MoveHistory::MoveHistory()
	: vector<size_t>()
{
	// 최소값 산출을 위한 초기값 INT_MAX
	hours = INT_MAX;
}
MoveHistory::MoveHistory(const Station &start)
	: vector<size_t>()
{
	reserve(stationArray.size() - 1);

	// 출발 역과 소요시간 0로 초기화함
	hours = 0;
	push_back(start.index);
}

bool MoveHistory::moveTo(const Station &dest)
{
	// 이동에 따른 추가 소요시간 계산
	// 기존 마지막 지점 -> dest
	hours += stationArray[back()].hoursArray[dest.index];

	if (front() == dest.index) // 출발 지점으로 돌아온 경우나
		return false;
	else if (minHoursArray[dest.index] < hours)
	{
		// 현재 방문하려는 지점이 과거 누군가가 방문했던 지점이며
		// 그 때 소요된 시간보다 더 많은 시간을 소요해서 도착했을 시에는
		// 실패로 간주
		return false;
	}
	else
	{
		minHoursArray[dest.index] = hours; // 최소 소요시간으로 등록을 하고
		push_back(dest.index); // 이동내역을 기록에 남김

		return true;
	}
}

void MoveHistory::print() const
{
	cout << hours << endl;

	for (size_t i = 0; i < size(); i++)
		cout << at(i) << " ";
}