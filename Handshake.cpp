#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * ����, �Ǽ�
 * http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=518&sca=30a0
 *
 * @author Samchon <http://samchon.org>
 */
class Handshake
{
private:
	/**
	 * ��ȣ �귣�带 ���� �迭.
	 *
	 * index: ������ ��ȣ
	 * value: ��ȣ �귣��
	 */
	vector<size_t> brandArray;

	/**
	 * Dynamic ����� ���� ��Ʈ����.
	 *
	 * ������ �Ǽ� ����� �����صд�.
	 */
	vector<vector<size_t>> handshakeMatrix;

public:
	/**
	 * Default Constructor.
	 */
	Handshake()
	{
		size_t brandSize;
		cin >> brandSize;

		brandArray.assign(brandSize, 0);
		handshakeMatrix.assign(brandSize, vector<size_t>(brandSize, -1));

		for (size_t i = 0; i < brandSize; i++)
			cin >> brandArray[i];
	};

	/**
	 * ���� �귣�� �� �Ǽ��� �� �ִ� �ִ밪�� ����
	 */
	auto calc() const -> size_t
	{
		return calc(0, brandArray.size());
	};

private:
	/**
	 * ���� ���� �� ���� �귣�� �� �Ǽ��� �� �ִ� �ִ밪�� ����.
	 *
	 * ���� �����Ͽ� �Ǽ��ϴ� ��찡 ������ �ʰԲ�
	 * �����Ͽ� �Ǽ� Ƚ���� ����Ѵ�.
	 */
	auto calc(size_t begin, size_t end) const -> size_t
	{
		if (begin >= end)
		{
			// ������ ����� ���
			return 0;
		}
		else  if (handshakeMatrix[begin][end - 1] != -1)
		{
			// �̹� ����� ���
			return handshakeMatrix[begin][end - 1];
		}

		size_t handshake = 0;
		for (size_t i = begin + 1; i < end; i += 2)
		{
			size_t myHandshake =
				(brandArray[begin] == brandArray[i] ? 1 : 0) // ���� �귣���̴� �Ǽ���, 1ȸ.
				+ calc(begin + 1, i) + calc(i + 1, end);
					// i�� �������� �������� �ɰ��� ����س���
					// �Ǽ��� �����Ͽ� ������ �ʰ� �ϱ� ���Ͽ�, �������� �ɰ���
					// ��������� ����س����� ���̴�.

			handshake = max(handshake, myHandshake);
		}

		// �̼��� �ð��ʰ� (1.018��) �� ���ϱ� ���� const�� �Բ� �޾Ƴ��� ��ġ�� ��,
		// �����δ� { handleshake[begin][end-1] = handshake; } �̴�.
		((vector<vector<size_t>>&)handshakeMatrix)[begin][end - 1] = handshake;
		return handshake;
	};
};

int main()
{
	Handshake handshake;

	cout << handshake.calc() << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}