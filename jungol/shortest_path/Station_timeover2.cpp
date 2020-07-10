#include <iostream>
#include <vector>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

class MoveHistory;
class Station;

/**
 * ��ü �� ����
 */
vector<Station> stationArray;

/**
 * �� ������ �̵��ϴ� �� �ҿ�� �ּ� �ð��� ���
 */
vector<int> minHoursArray;

/**
 * ����ö �� Ŭ����.
 *
 * ���� ��ȣ�� ���� �� �� �ش� �������� �̵��� �ҿ�ð��� ����.
 */
class Station
{
	friend class MoveHistory;

private:
	/**
	 * ���� ���� ��ȣ.
	 */
	size_t index;

	/**
	 * �̿��� ������ �̵��ϴ� �� �ҿ�Ǵ� �ð�
	 */
	vector<int> hoursArray;

public:
	Station(size_t);

	/**
	* �̿��� ���� �̵� �ҿ�ð��� ������.
	*/
	void setNeighbor(const Station &, int);

	/**
	* Ư�� ������ �̵��� ��, ���� ª�� �ð��� �ҿ�Ǵ� �̵���θ� ����.
	*
	* @param destination ��ǥ ��
	*
	* @return �̵� ���� �� �ҿ�ð�
	*/
	MoveHistory moveTo(const Station &) const;

private:
	/**
	 * Ư�� ������ �̵�, ��׶��� �޼ҵ�.
	 * ������ �̵������� ���Ͽ� Ư�� ������ �̵��� �� �ִ� ���� ª�� ��θ� ã�´�.
	 *
	 * @param destination ��ǥ ��
	 * @param moveHistory ���������� �̵�����
	 *
	 * @return �̵� ���� �� �ҿ�ð�
	 */
	MoveHistory moveTo(const Station &, const MoveHistory &) const;
};

/**
 * �̵����� Ŭ����.
 *
 * �湮�� ��(Station)�� �ҿ�ð� ������ ����.
 */
class MoveHistory
	: vector<size_t>
{
	friend class Station;

private:
	/**
	 * ���� �̵������� �Ҹ��� �ð�
	 */
	int hours;

public:
	/**
	* �⺻ ������.
	*
	* hours�� INT_MAX�� ��. �ּҰ� ���������� �ʱⰪ ������ ���.
	*/
	MoveHistory();

	/**
	* ������ from �������
	*
	* @param start ��߿�
	*/
	MoveHistory(const Station &);

	/**
	* Ư�� ������ �̵��ϸ�, ������ �ҿ�ð� ���� �����.
	*
	* ���� �̵��Ϸ��� ���� ���ſ� �ٸ� MoveHistory�� �̹� ���İ� ���̸�, ������ �ҿ�ð���
	* ������ �ҿ�ð����� �� ª�� ��, ������ �̵��� ���ǹ��� ������ �� false�� �����Ѵ�.
	*
	* @return Ư�� �������� �̵��� ���ǹ��� ��� false
	*/
	bool moveTo(const Station &);

	/**
	* ��� ���
	*/
	void print() const;
};

/* ---------------------------------------------------------
	MAIN
--------------------------------------------------------- */
int main()
{
	//////////////////////////////
	// Station �� �ҿ�ð� ����
	//////////////////////////////
	size_t size, destIndex;
	cin >> size >> destIndex;

	// Station ����
	stationArray.assign(size + 1, Station(0));
	minHoursArray.assign(size + 1, INT_MAX);
	
	for (size_t i = 1; i <= size; i++)
		stationArray[i] = Station(i);

	// �ҿ�ð� ����
	for (size_t i = 1; i <= size; i++)
		for (size_t j = 1; j <= size; j++)
		{
			int hours;
			cin >> hours;

			stationArray[i].setNeighbor(stationArray[j], hours);
		}

	//////////////////////////////
	// �ּ� �ҿ�ð� ����
	//////////////////////////////
	const Station &start = stationArray[1];
	const Station &dest = stationArray[destIndex];

	// ���
	const MoveHistory &moveHistory = start.moveTo(dest);

	// �ּ� �ҿ�ð� ���� ���
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
	MoveHistory minHistory; // �ʱ��, INT_MAX

	for (size_t i = 1; i < hoursArray.size(); i++)
	{
		// �ڱ� �ڽſ��Է� �̵������� ����
		if (i == this->index)
			continue;

		MoveHistory myHistory(*this); // �̵� ����
		const Station &next = stationArray[i]; // �������� �̵��� ��

		// �ش� �������� �̵��� ���ǹ����� �˻�
		if (myHistory.moveTo(next) == false)
			continue;

		// ���ǹ��ϴٸ� �̵��� �ǽ�
		myHistory = next.moveTo(dest, myHistory);

		// ������ �̵����� �ҿ�ð��� �ּ��ΰ�?
		if (myHistory.hours < minHistory.hours)
			minHistory = myHistory;
	}

	return minHistory;
}
MoveHistory Station::moveTo(const Station &dest, const MoveHistory &moveHistory) const
{
	if (this == &dest)
		return moveHistory;

	MoveHistory minHistory; // �ʱ��, INT_MAX

	for (size_t i = 1; i < hoursArray.size(); i++)
	{
		// �ڱ� �ڽſ��Է� �̵������� ����
		if (i == this->index)
			continue;

		MoveHistory myHistory = moveHistory;
		const Station &next = stationArray[i]; // �������� �̵��� ��

		if (myHistory.moveTo(next) == false) // �ش� �������� �̵��� ���ǹ����� �˻�
			continue;

		// ���ǹ��ϴٸ� �̵��� �ǽ�
		myHistory = next.moveTo(dest, myHistory);

		// ������ �̵����� �ҿ�ð��� �ּ��ΰ�?
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
	// �ּҰ� ������ ���� �ʱⰪ INT_MAX
	hours = INT_MAX;
}
MoveHistory::MoveHistory(const Station &start)
	: vector<size_t>()
{
	reserve(stationArray.size() - 1);

	// ��� ���� �ҿ�ð� 0�� �ʱ�ȭ��
	hours = 0;
	push_back(start.index);
}

bool MoveHistory::moveTo(const Station &dest)
{
	// �̵��� ���� �߰� �ҿ�ð� ���
	// ���� ������ ���� -> dest
	hours += stationArray[back()].hoursArray[dest.index];

	if (front() == dest.index) // ��� �������� ���ƿ� ��쳪
		return false;
	else if (minHoursArray[dest.index] < hours)
	{
		// ���� �湮�Ϸ��� ������ ���� �������� �湮�ߴ� �����̸�
		// �� �� �ҿ�� �ð����� �� ���� �ð��� �ҿ��ؼ� �������� �ÿ���
		// ���з� ����
		return false;
	}
	else
	{
		minHoursArray[dest.index] = hours; // �ּ� �ҿ�ð����� ����� �ϰ�
		push_back(dest.index); // �̵������� ��Ͽ� ����

		return true;
	}
}

void MoveHistory::print() const
{
	cout << hours << endl;

	for (size_t i = 0; i < size(); i++)
		cout << at(i) << " ";
}