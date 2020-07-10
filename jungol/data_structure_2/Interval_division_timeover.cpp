#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ElementArray
	: public vector<int>
{
private:
	typedef vector<int> super;

public:
	using super::super;

	auto calcMax(size_t begin, size_t end) -> int
	{
		// �ִ밪
		int val;

		if (end - begin >= 2)
		{
			// ���Ϸ��� ���� ũ�Ⱑ 2�� �Ѿ��
			// �����Ͽ� ���
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

		return val;
	};
};

int main()
{
	ElementArray elementArray;
	
	/////////////////////////////////////////////////////
	// ������ ����
	/////////////////////////////////////////////////////
	size_t elementSize, intervalSize;
	cin >> elementSize >> intervalSize;

	elementArray.assign(elementSize, 0);
	
	// �� ���� �Է�
	for (size_t i = 0; i < elementArray.size(); i++)
		cin >> elementArray[i];

	/////////////////////////////////////////////////////
	// �� ������ �ִ밪 ��� & ���
	/////////////////////////////////////////////////////
	for (size_t i = 0; i < intervalSize; i++)
	{
		size_t begin;
		size_t end;

		cin >> begin >> end;
		cout << elementArray.calcMax(begin - 1, end) << endl;
	}

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}