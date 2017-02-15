#include <iostream>
using namespace std;

#define uint64 unsigned long long
#define REMAINDER 20091024

/**
 * X^Y �� 20091024 ���� �� �������� ����
 *
 * @param x ����
 * @param y �¼�
 * @return ������
 */
auto power(uint64 x, uint64 y) -> uint64
{
	if (y == 0)
		return 1;
	else if (y == 1)
		return x;
	else // if (y >= 2)
	{
		uint64 value = power(x, y / 2); // �¼��� ������ �ɰ� ��
		value = value * value; // �� ������� ������

		if (value >= REMAINDER)
			value %= REMAINDER;

		if (y % 2 == 1) // Ȧ���� �ٽ� x�� �� �� �� ����
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