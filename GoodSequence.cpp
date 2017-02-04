#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

size_t cipher;

class GoodSequence
{
private:
	/**
	 * 구하고자 하는 좋은 수열의 자릿수
	 */
	size_t cipher;

	/**
	 * 가장 좋은 수열
	 */
	string best;
	
public:
	/**
	 * Construct from a cipher.
	 */
	GoodSequence(size_t cipher)
	{
		this->cipher = cipher;
	};

	/**
	 * 좋은 수열을 찾는다
	 */
	void find()
	{
		find("");
	};

	/**
	 * Get 좋은 수열.
	 */
	auto getBest() const -> string
	{
		return best;
	};

private:
	/**
	 * 좋은 수열을 찾는 재귀함수.
	 *
	 * @param str 현재까지 완성된 좋은 수열
	 */
	void find(const string &str)
	{
		if (best.empty() == false)
		{
			// 최고의 수열이 이미 구해졌다면
			return;
		}
		else if (isValid(str) == false)
		{
			// 현재 수열이 나쁘다면
			return;
		}
		else if (str.size() == cipher)
		{
			// 마지막 자릿수까지 도착했다면
			this->best = str;
			return;
		}

		// 현재의 수열에 1, 2 또는 3을 추가하면서 계속 탐색해 나간다
		find(str + '1');
		find(str + '2');
		find(str + '3');
	};

	/**
	 * 유효한 (좋은) 수열인지 검사
	 *
	 * @param str 수열
	 */
	auto isValid(const string &str) const -> bool
	{
		if (str.size() <= 1)
			return true;

		size_t halfSize = str.size() / 2;
		for (size_t i = 1; i <= halfSize; i++)
		{
			// 현재의 수열을 뒷 자리로부터 i개씩 끊어서
			size_t middle = str.size() - i;

			// 같은 지를 비교. 같으면 나쁜 수열이 된다.
			if (str.substr(middle, i) == str.substr(middle - i, i))
				return false;
		}

		return true;
	};
};

int main()
{
	size_t cipher;
	cin >> cipher;

	GoodSequence goodSequence(cipher);
	goodSequence.find();

	cout << goodSequence.getBest() << endl;

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}