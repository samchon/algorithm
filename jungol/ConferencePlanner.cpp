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
	 * ���� �ð� ���������� ���� ���� �޼ҵ�.
	 * ���� �ð��� ���� ���ٸ�, ���� �ð����� �������� ������ �Ѵ�.
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
		// ȸ�� ����� ���� �ð��� �������� ����
		sort(conferenceArray.begin(), conferenceArray.end());

		// ���� ù ȸ�Ǹ� ���� ��ȹ�� �߰���
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