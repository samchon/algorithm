#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/**
 * ���� Ŭ����
 */
class Paper
{
private:
	/**
	 * ���� ����
	 */
	int width;

	/**
	 * ���� ����
	 */
	int height;

	// ���� ���̿� ���� �� �ִ� ���̵�
	vector<const Paper*> putArray;

public:
	/** 
	 * Construct from members.
	 *
	 * @param width ���� ����
	 * @param height ���� ����
	 */
	Paper(int width, int height)
	{
		if (width > height)
			swap(width, height);

		this->width = width;
		this->height = height;
	};
	
	/**
	 * ���� ���̿� �ٸ� ���̸� ��´�.
	 */
	void put(const Paper *paper)
	{
		if (this == paper)
			return;

		if ((width >= paper->width && height >= paper->height) ||
			(width >= paper->height && height >= paper->width))
		{
			putArray.push_back(paper);
		}
	};

	/**
	 * ���� ���̿� ���� �� �ִ� �ִ� ���� ���� ����.
	 */
	auto count() const -> size_t
	{
		return count(1, {});
	};

private:
	/**
	 * ���� ���̿� ���� �� �ִ� �ִ� ���� ���� ����.
	 * ��� Ž���� ����.
	 *
	 * @param step �̹� �����ִ� ������ ����
	 * @param stacked �̹� �����ִ� ���̵�. �ߺ� ������ ����
	 */
	auto count(size_t step, set<const Paper*> stacked) const -> size_t
	{
		stacked.insert(this);

		size_t size = step;

		for (size_t i = 0; i < putArray.size(); i++)
			if (stacked.count(putArray[i]) != 0)
				continue;
			else
				size = max(size, putArray[i]->count(step + 1, stacked));

		return size;
	};
};

int main()
{
	vector<Paper> paperArray;
	size_t size;

	// --------------------------------------------
	// ������ �Է�
	// --------------------------------------------
	cin >> size;
	paperArray.reserve(size);

	for (size_t i = 0; i < size; i++)
	{
		int width;
		int height;

		cin >> width >> height;
		paperArray.push_back(Paper(width, height));
	}

	// --------------------------------------------
	// ���
	// --------------------------------------------
	// ���̸� ��
	for (size_t i = 0; i < paperArray.size(); i++)
		for (size_t j = 0; j < paperArray.size(); j++)
			if (i == j)
				continue;
			else
				paperArray[i].put(&paperArray[j]);
	
	// �ִ�� ���� �� �ִ� ���� ���� ���
	size_t maxSize = 0;
	for (size_t i = 0; i < paperArray.size(); i++)
		maxSize = max(maxSize, paperArray[i].count());

	// ���
	cout << maxSize << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}