#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

/**
 * �ع� Ŭ����.
 */
class Hamming
{
private:
	/**
	 * �ڵ� �迭.
	 */
	vector<int> codeArray;

	/**
	 * �ڵ� ��.
	 */
	map<int, size_t> codeMap;

	/**
	 * ã���� �ϴ� �عְ���� ���� index.
	 */
	size_t begin;

	/**
	 * ã���� �ϴ� �عְ���� �� index.
	 */
	size_t end;

	/**
	 * ã���� �ϴ� �� �عְ���� ũ�� ����.
	 */
	int gap;

	/**
	 * gap�� �����ΰ��� ���� flag ����.
	 */
	bool negative;

	vector<size_t> phaseArray;

public:
	/**
	 * Default Constructor.
	 */
	Hamming()
	{
		size_t size;
		size_t cipher;

		cin >> size >> cipher;
		codeArray.assign(size + 1, 0);

		for (size_t i = 1; i <= size; i++)
		{
			string bits;
			cin >> bits;

			int value = fetchValue(bits);

			codeArray[i] = value;
			codeMap.insert({ value, i });
		}
		cin >> begin >> end;
		
		gap = codeArray[end] - codeArray[begin];
		if (gap < 0)
		{
			swap(begin, end);
			negative = true;
		}
	};

	auto findPhase(int step = 1) -> bool
	{
		if (step == codeArray[end] - codeArray[begin])
			return false;
		
		phaseArray.clear();
		phaseArray.push_back(begin);

		for (int i = codeArray[begin] + step; i < codeArray[end]; i++)
			if (codeMap.count(i) == 0)
			{
				for (int k = step; k <= gap; k++)
					if (gap % k != 0)
						continue;
					else
						return findPhase(k);
			}
			else
				phaseArray.push_back(codeMap[i]);

		phaseArray.push_back(end);
		return true;
	};

	void printPhase() const
	{
		vector<size_t> phaseArray;
		if (negative == true)
			phaseArray.assign(this->phaseArray.rbegin(), this->phaseArray.rend());
		else
			phaseArray = this->phaseArray;

		for (size_t i = 0; i < phaseArray.size(); i++)
			cout << phaseArray[i] << " ";
	};

private:
	static int fetchValue(const string &bits)
	{
		int val = 0;

		for (size_t i = 0; i < bits.size(); i++)
			if (bits[i] == '1')
				val++;

		return val;
	};
};

int main()
{
	Hamming hamming;
	bool result = hamming.findPhase();

	if (result == false)
		cout << -1 << endl;
	else
		hamming.printPhase();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}