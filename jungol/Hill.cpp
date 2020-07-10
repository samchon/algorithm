#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#	define INT_MIN (INT_MAX + 1)
#endif

int main()
{
	size_t size;
	vector<int> valueArray;
	
	cin >> size;
	valueArray.assign(size, 0);

	for (size_t i = 0; i < size; i++)
		cin >> valueArray[i];

	int maxHeight = -1;
	int height = 0;

	for (size_t i = 1; i < valueArray.size(); i++)
	{
		int myHeight = valueArray[i] - valueArray[i - 1];
		if (myHeight > 0)
		{
			height += myHeight;
		}
		else
		{
			maxHeight = max(height, maxHeight);
			height = 0;
		}
	}
	maxHeight = max(height, maxHeight);

	cout << maxHeight << endl;

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}