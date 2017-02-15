#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class ElementArray
	: public vector<int>
{
private:
	typedef vector<int> super;

	map<pair<size_t, size_t>, int> intervalMap;

public:
	using super::super;

	auto calcMax(size_t begin, size_t end) -> int
	{
		auto it = intervalMap.find({ begin, end });
		{
			// �̹� ���س��� �����̸�, �̸� ���
			if (it != intervalMap.end())
				return it->second;
		}

		// �ִ밪
		int val;

		if (end - begin >= 2)
		{
			// ���Ϸ��� ���� ũ�Ⱑ 2�� �Ѿ��
			// �����Ͽ� ���
			// �׷��� map�� index ���߷��� ��������
			size_t middle = (begin + end) / 2;

			int front = calcMax(begin, middle); // ���� ��
			int back = calcMax(middle, end); // ���� ��

			val = max(front, back);
		}
		else
		{
			// ���� �� FULL SCANNING
			val = this->at(begin);

			for (size_t i = begin + 1; i < end; i++)
				val = max(val, this->at(i));
		}

		// ������ ���� �ִ밪�� map�� index key�� �Բ� ����
		intervalMap[{begin, end}] = val;

		return val;
	};
};

int main()
{
	ElementArray elementArray;
	vector<pair<size_t, size_t>> intervalArray;

	/////////////////////////////////////////////////////
	// ������ ����
	/////////////////////////////////////////////////////
	size_t elementSize, intervalSize;
	cin >> elementSize >> intervalSize;

	elementArray.assign(elementSize, 0);
	intervalArray.assign(intervalSize, {0, 0});

	// �� ���� �Է�
	for (size_t i = 0; i < elementArray.size(); i++)
		cin >> elementArray[i];

	// �� �������� �Է�
	for (size_t i = 0; i < intervalArray.size(); i++)
	{
		pair<size_t, size_t> &interval = intervalArray[i];

		cin >> interval.first; 
		interval.first--; // 1�� ������ ��
		cin >> interval.second;
	}

	/////////////////////////////////////////////////////
	// �� ������ �ִ밪 ��� & ���
	/////////////////////////////////////////////////////
	for (size_t i = 0; i < intervalArray.size(); i++)
	{
		pair<size_t, size_t> &interval = intervalArray[i];

		cout << elementArray.calcMax(interval.first, interval.second) << endl;
	}

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}