#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

/**
 * ������ ���.
 *
 * �� ������ ���� �̵��� �ʿ��� �ּ� Ŭ������ �����س��� ���.
 * �̵��� �Ұ��� ��쿡�� INT_MAX, �̵��� ������ ��� �ʱⰪ�� 1.
 */
class PageMatrix
	: public vector<vector<int>>
{
private:
	typedef vector<vector<int>> super;

public:
	/**
	 * Construct from ��� ������.
	 */
	PageMatrix(size_t size)
		: super(size, vector<int>(size, INT_MAX))
	{
	};
	
	/**
	 * �� ������ ���� �̵��� �ʿ��� �ּ� Ŭ������ ����Ѵ�.
	 */
	void calcDepth()
	{
		for (size_t k = 0; k < size(); k++) // ����
			for (size_t i = 0; i < size(); i++) // ��
				for (size_t j = 0; j < size(); j++) // ��
				{
					if (i == j)
						continue;
					else if (at(i).at(k) == INT_MAX || at(k).at(j) == INT_MAX)
					{
						// ���� ��ΰ� �������� �ʴ´ٸ� PASS
						continue;
					}
					int &depth = at(i).at(j);
					int newDepth = at(i).at(k) + at(k).at(j);

					// ���� ��ΰ� ������ ��κ��� �� ª�ٸ�, �����Ѵ�
					depth = min(depth, newDepth);
				}
	};
	
public:
	/**
	 * �� ������ �� �̵��� �ʿ��� Ŭ������ ��հ��� �����.
	 */
	auto calcAverage() const -> double
	{
		int nominator = 0.0;
		double denominator = (size() - 1) * size();

		for (size_t i = 0; i < size(); i++)
			for (size_t j = 0; j < size(); j++)
			{
				if (i == j || at(i).at(j) == INT_MAX)
					continue;
				else
					nominator += at(i).at(j);
			}

		return nominator / denominator;
	};
};

int main()
{
	// -------------------------------------------------
	//	������ ����
	// -------------------------------------------------
	// ���� ��ũ ��θ� ������ �Է¹޴´�.
	vector<pair<size_t, size_t>> linkArray;
	size_t linkSize;
	cin >> linkSize;

	size_t size = 0;

	for (size_t i = 0; i < linkSize; i++)
	{
		size_t from, to;
		cin >> from >> to;
		
		// �� ���߿� ����Ʈ ������ �����س���
		size = max(size, max(from, to));

		// ��ũ �迭�� �߰�
		linkArray.push_back({from - 1, to - 1});
	}

	// ������ ��� ����
	PageMatrix stationMatrix(size);
	for (size_t i = 0; i < linkArray.size(); i++)
	{
		const pair<size_t, size_t> &link = linkArray[i];

		stationMatrix.at(link.first).at(link.second) = 1;
	}

	// -------------------------------------------------
	//	�ִ� ��� (Ŭ����) ���
	// -------------------------------------------------
	stationMatrix.calcDepth();

	// -------------------------------------------------
	//	��� ���
	// -------------------------------------------------
	// �Ҽ� �� ��° �ڸ��� �����ϱ� ���� C++ �Լ�
	cout << fixed;
	cout.precision(3);

	// ��� Ŭ�� Ƚ�� ���
	cout << stationMatrix.calcAverage() << endl;

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}