#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

/**
 * 해밍 클래스.
 */
class Hamming
{
private:
	/**
	 * 코드 배열.
	 */
	vector<int> codeArray;

	/**
	 * 코드 맵.
	 */
	map<int, size_t> codeMap;

	/**
	 * 찾고자 하는 해밍경로의 시작 index.
	 */
	size_t begin;

	/**
	 * 찾고자 하는 해밍경로의 끝 index.
	 */
	size_t end;

	/**
	 * 찾고자 하는 두 해밍경로의 크기 차이.
	 */
	int gap;

	/**
	 * gap이 음수인가에 대한 flag 변수.
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