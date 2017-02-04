#include <iostream>
#include <list>

typedef unsigned long long uint64;
using namespace std;

/*
0
9
999999999
1000000000
804289385
846930887
681692779
714636917
957747795
424238336
719885387
649760494
596516650
189641423
-1
*/

auto fibonacci(uint64 x) -> uint64
{
	if (x == 0)
		return 0;
	else if (x == 1)
		return 1;

	if (x > 10000)
		if (x % 10000 == 0)
			return fibonacci(9998) + fibonacci(9999);
		else
			x = x % 10000;

	uint64 a = 0, b = 1;
	uint64 c = 0;

	for (uint64 i = 2; i <= x; i++)
	{
		c = a + b;
		if (c > 10000)
			c = c % 10000;

		a = b;
		b = c;
	}
	return c;
}

int main()
{
	list<uint64> questionList;

	while (true)
	{
		uint64 x;
		cin >> x;

		if (x == -1)
			break;

		cout << "\t" << fibonacci(x) << endl;
		//questionList.push_back(x);
	}

	//for (auto it = questionList.begin(); it != questionList.end(); it++)
		//cout << fibonacci(*it) << endl;

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}