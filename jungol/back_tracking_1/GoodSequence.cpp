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
	 * ���ϰ��� �ϴ� ���� ������ �ڸ���
	 */
	size_t cipher;

	/**
	 * ���� ���� ����
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
	 * ���� ������ ã�´�
	 */
	void find()
	{
		find("");
	};

	/**
	 * Get ���� ����.
	 */
	auto getBest() const -> string
	{
		return best;
	};

private:
	/**
	 * ���� ������ ã�� ����Լ�.
	 *
	 * @param str ������� �ϼ��� ���� ����
	 */
	void find(const string &str)
	{
		if (best.empty() == false)
		{
			// �ְ��� ������ �̹� �������ٸ�
			return;
		}
		else if (isValid(str) == false)
		{
			// ���� ������ ���ڴٸ�
			return;
		}
		else if (str.size() == cipher)
		{
			// ������ �ڸ������� �����ߴٸ�
			this->best = str;
			return;
		}

		// ������ ������ 1, 2 �Ǵ� 3�� �߰��ϸ鼭 ��� Ž���� ������
		find(str + '1');
		find(str + '2');
		find(str + '3');
	};

	/**
	 * ��ȿ�� (����) �������� �˻�
	 *
	 * @param str ����
	 */
	auto isValid(const string &str) const -> bool
	{
		if (str.size() <= 1)
			return true;

		size_t halfSize = str.size() / 2;
		for (size_t i = 1; i <= halfSize; i++)
		{
			// ������ ������ �� �ڸ��κ��� i���� ���
			size_t middle = str.size() - i;

			// ���� ���� ��. ������ ���� ������ �ȴ�.
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