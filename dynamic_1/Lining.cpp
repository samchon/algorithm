#include <iostream>
#include <vector>
#include <algorithm>

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

using namespace std;

int main()
{
	vector<size_t> indexArray;
	vector<size_t> lisArray;
	size_t size;
	size_t arrange = 0;

	cin >> size;
	indexArray.assign(size, 0);
	lisArray.assign(size, 0);

	for (size_t i = 0; i < size; i++)
		cin >> indexArray[i];

	// ������������ ���� ū ������ ã�Ƴ� - �������
	for (size_t i = 0; i < size; i++)
	{
		lisArray[i] = 1;

		for (size_t j = 0; j < i; j++)
			if (indexArray[j] < indexArray[i])
				lisArray[i] = max(lisArray[i], lisArray[j] + 1);
	}

	for (size_t i = 0; i < lisArray.size(); i++)
		arrange = max(arrange, lisArray[i]);

	// ��ü ���̿��� ��������� �� ��ŭ�� �����ϸ� �ȴ�
	cout << (size - arrange) << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}