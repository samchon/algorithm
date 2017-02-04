#include <iostream>
#include <stack>

using namespace std;

/*
5
6 9 5 7 4
*/

// ���� �� ġ��������
// ���� ���� �Է��Ѵ�

class Tower
{
public:
	size_t index;
	int height;
	Tower *listener;

	Tower(size_t index)
	{
		this->index = index;
		cin >> this->height;

		listener = nullptr;
	};
};

int main()
{
	stack<Tower> towerStack;
	size_t size;
	cin >> size;

	for (size_t i = 1; i <= size; i++)
	{
		Tower tower(i);

		while (towerStack.empty() == false)
		{
			if (towerStack.top().height < tower.height)
				towerStack.pop();
			else
				break;
		}

		// �� Ƚ������ ���÷� ����� �ϴ� timeover�� ����
		// �۽� Ÿ���� ������ ������ ��, �ϰ� ����� �ؾ� �� ����
		if (towerStack.empty() == true)
			cout << "0 ";
		else
			cout << towerStack.top().index << " ";
		
		towerStack.push(tower);
	}

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}