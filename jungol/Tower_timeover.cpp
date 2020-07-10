#include <iostream>
#include <stack>

using namespace std;

/*
5
6 9 5 7 4
*/

// 낮은 건 치워버리고
// 높은 것은 입력한다

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

		// 매 횟수마다 수시로 출력을 하니 timeover가 난다
		// 송신 타워를 따로이 설정한 후, 일괄 출력을 해야 할 듯함
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