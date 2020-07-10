#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

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

public:
	/** 
	 * Construct from members.
	 *
	 * �Էµ� ���� ���̰� �� ũ��, ���ο� ������ ���� �ٲ۴�.
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
	 * ������ Paper�� ��� Paper���� ������ ��. 
	 * ���� ũ����� ��, ���� ũ�Ⱑ ���� ���� ���� ũ�⸦ ��
	 */
	auto operator<(const Paper &obj) const -> bool
	{
		if (width == obj.width)
			return height < obj.height;
		else
			return width < obj.width;
	};

	/**
	 * ������ Paper�� Ÿ�� Paper�� ����(����) �� �ִ°�
	 */
	auto containable(const Paper &obj) const -> bool
	{
		return (width >= obj.width && height >= obj.height)
			|| (width >= obj.height && height >= obj.width);
	};
};

int main()
{
	vector<Paper> paperArray;
	vector<size_t> sizeArray;
	size_t size;
	
	// --------------------------------------------
	// ������ �Է�
	// --------------------------------------------
	cin >> size;
	paperArray.reserve(size);
	sizeArray.assign(size, 1);

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
	// ���� �迭�� ������������ ����
	sort(paperArray.begin(), paperArray.end());

	// ���̳������� ũ��迭�� ����
	for (size_t i = 1; i < paperArray.size(); i++)
		for (size_t j = 0; j < i; j++)
			if (paperArray[i].containable(paperArray[j]) && sizeArray[i] < sizeArray[j] + 1)
			{
				// i��° ���̿� j��° ���̸� ���� �� �ִٸ�,
				// j��° ���̱��� ����� ���� ������ +1
				sizeArray[i] = sizeArray[j] + 1;
			}

	// ������ ���� ū��
	size_t maxSize = 0;
	for (size_t i = 0; i < sizeArray.size(); i++)
		maxSize = max(maxSize, sizeArray[i]);
	
	// --------------------------------------------
	// ���
	// --------------------------------------------
	cout << (maxSize) << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}