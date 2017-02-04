#include <iostream>
using namespace std;

#define uint64 unsigned long long
#define REMAINDER 20091024

/**
 * X^Y 를 20091024 나눠 그 나머지를 구함
 *
 * @param x 지수
 * @param y 승수
 * @return 나머지
 */
auto power(uint64 x, uint64 y) -> uint64
{
	if (y == 0)
		return 1;
	else if (y == 1)
		return x;
	else // if (y >= 2)
	{
		uint64 value = power(x, y / 2); // 승수를 반으로 쪼갠 뒤
		value = value * value; // 그 결과값을 제곱함

		if (value >= REMAINDER)
			value %= REMAINDER;

		if (y % 2 == 1) // 홀수면 다시 x를 한 번 더 곱함
		{
			value *= x;

			if (value >= REMAINDER)
				value %= REMAINDER;
		}
		return value;
	}
}

int main()
{
	unsigned long long x, y;
	cin >> x >> y;

	cout << power(x, y) << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}