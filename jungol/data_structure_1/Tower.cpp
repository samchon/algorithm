#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Tower
{
public:
	/**
	 * Ÿ���� ��ȣ
	 */
	size_t index;

	/**
	 * Ÿ���� ����
	 */
	int height;

	/**
	 * ���� Ÿ���� ���ĸ� �۽��ϰ� �� �� �ٸ� Ÿ��
	 */
	Tower *listener;

public:
	/**
	 * ������ from index ��ȣ.
	 */
	Tower(size_t index)
	{
		this->index = index;
		cin >> height;

		listener = nullptr;
	};

	/**
	 * �۽� Ÿ�� ��ȣ�� �����
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
	// Ÿ�� ��� ����
	// ---------------------------------------
	towerArray.reserve(size);
	for (size_t i = 1; i <= size; i++)
		towerArray.push_back(Tower(i));

	// ---------------------------------------
	// �۽� Ÿ���� ã��
	// ---------------------------------------
	for (size_t i = 0; i < towerArray.size(); i++)
	{
		Tower *tower = &towerArray[i];

		while (towerStack.empty() == false)
		{
			if (towerStack.top()->height < tower->height)
			{
				// ���ÿ� ��ϵǾ��ִ� ������ Ÿ���� ���̰� �� ���ٸ�
				// ������
				towerStack.pop();
			}
			else
			{
				// ���ÿ� ��ϵ� ������ Ÿ���� �� Ÿ������ ���ٸ�
				// �۽� Ÿ���� ���Ű ���� whlie���� ����
				break;
			}
		}

		if (towerStack.empty() == false)
		{
			// ���ÿ� ���� Ÿ���� �ִٸ�,
			// �̴� ���� ����� ���� �����ϴ� �� ���� Ÿ���� �ǹ��ϴ�
			// ��� Ÿ���� ����Ѵ�
			tower->listener = towerStack.top();
		}

		// ������ Ÿ���� ���ÿ� ���
		towerStack.push(tower);
	}

	// ---------------------------------------
	// ��� ���
	// ---------------------------------------
	for (size_t i = 0; i < towerArray.size(); i++)
		towerArray[i].print();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}