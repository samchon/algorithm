#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Tower
{
public:
	/**
	 * 타워의 번호
	 */
	size_t index;

	/**
	 * 타워의 높이
	 */
	int height;

	/**
	 * 현재 타워의 전파를 송신하게 될 또 다른 타워
	 */
	Tower *listener;

public:
	/**
	 * 생성자 from index 번호.
	 */
	Tower(size_t index)
	{
		this->index = index;
		cin >> height;

		listener = nullptr;
	};

	/**
	 * 송신 타워 번호를 출력함
	 */
	void print() const
	{
		if (listener == nullptr)
			cout << "0 ";
		else
			cout << listener->index << " ";
	};
};

int main()
{
	vector<Tower> towerArray;
	stack<Tower*> towerStack;

	size_t size;
	cin >> size;

	// ---------------------------------------
	// 타워 목록 구성
	// ---------------------------------------
	towerArray.reserve(size);
	for (size_t i = 1; i <= size; i++)
		towerArray.push_back(Tower(i));

	// ---------------------------------------
	// 송신 타워를 찾음
	// ---------------------------------------
	for (size_t i = 0; i < towerArray.size(); i++)
	{
		Tower *tower = &towerArray[i];

		while (towerStack.empty() == false)
		{
			if (towerStack.top()->height < tower->height)
			{
				// 스택에 등록되어있는 기존의 타워의 높이가 더 낮다면
				// 버린다
				towerStack.pop();
			}
			else
			{
				// 스택에 등록된 기존의 타워가 현 타워보다 높다면
				// 송신 타워로 등록키 위해 whlie문을 끝냄
				break;
			}
		}

		if (towerStack.empty() == false)
		{
			// 스택에 남은 타워가 있다면,
			// 이는 가장 가까운 곳에 존재하는 더 높은 타워를 의미하니
			// 통신 타워로 등록한다
			tower->listener = towerStack.top();
		}

		// 현재의 타워도 스택에 등록
		towerStack.push(tower);
	}

	// ---------------------------------------
	// 결과 출력
	// ---------------------------------------
	for (size_t i = 0; i < towerArray.size(); i++)
		towerArray[i].print();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}