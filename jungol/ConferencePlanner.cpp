#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Conference
{
public:
	int index;
	int startTime;
	int endTime;

	Conference()
	{
	};

	/**
	 * 종료 시간 내림차순을 위한 정렬 메소드.
	 * 종료 시간이 서로 같다면, 시작 시간으로 내림차순 정렬을 한다.
	 */
	bool operator<(const Conference &obj) const
	{
		if (endTime != obj.endTime)
			return endTime < obj.endTime;
		else
			return startTime < obj.startTime;
	};
};

class ConferencePlanner
{
private:
	vector<Conference> conferenceArray;

public:
	ConferencePlanner()
	{
		size_t size;
		cin >> size;

		conferenceArray.assign(size, Conference());
		for (size_t i = 0; i < size; i++)
		{
			cin >> conferenceArray[i].index;
			cin >> conferenceArray[i].startTime;
			cin >> conferenceArray[i].endTime;
		}
	};

	void plan()
	{
		// 회의 목록을 종료 시간을 기준으로 정렬
		sort(conferenceArray.begin(), conferenceArray.end());

		// 가장 첫 회의를 먼저 계획에 추가함
		vector<Conference*> planArray;
		planArray.push_back(&conferenceArray.front());

		for (size_t i = 0; i < conferenceArray.size(); i++)
		{
			Conference *lastPlan = planArray.back();
			if (lastPlan->endTime <= conferenceArray[i].startTime)
				planArray.push_back(&conferenceArray[i]);
		}

		cout << planArray.size() << endl;
		for (size_t i = 0; i < planArray.size(); i++)
			cout << planArray[i]->index << " ";
	};
};

int main()
{
	ConferencePlanner planner;
	planner.plan();

	return 0;
}