#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * ���� Ŭ����.
 */
class Interval
{
public:
	/**
	 * ���� �ð�.
	 */
	size_t begin;

	/**
	 * ���� �ð�.
	 */
	size_t end;

	/**
	 * Construct from members.
	 *
	 * @param begin ���� �ð�
	 * @param end ���� �ð�
	 */
	Interval(size_t begin, size_t end)
	{
		this->begin = begin;
		this->end = end;
	};

	/**
	 * ������ ���ݰ� Ÿ�� ���ݿ� �������� �ִ� �� �˻�.
	 *
	 * @param interval Ÿ�� ����
	 * @return �������� �ִ� �� ����
	 */
	auto intersects(const Interval &interval) const -> bool
	{
		// 1 ~ 3
		// 3 ~ 5

		// 3 is not greater than 1
		// 1 is not greater than 5
		return !(begin > interval.end || interval.begin > end);
	};

	/**
	 * ��� �� �Լ�.
	 * 
	 * ���� �ð��� �� ���� �� �˻��Ѵ�.
	 */
	auto operator<(const Interval &interval) const -> bool
	{
		if (begin == interval.begin)
			return end < interval.end;
		else
			return begin < interval.begin;
	};

	/**
	 * Get �������� �ӹ��� �ð�.
	 */
	auto stay() -> size_t
	{
		return end - begin;
	};

	/** 
	 * ������ ������ Ÿ�� ���ݰ��� ���������� Ȯ��.
	 *
	 * @param interval Ÿ�� ����
	 */
	void expand(const Interval &interval)
	{
		begin = min(begin, interval.begin);
		end = max(end, interval.end);
	};
};

/** 
 * ������ Ŭ����.
 */
class Library
{
private:
	/**
	 * ���� �迭.
	 */
	vector<Interval> intervalArray;

public:
	/**
	 * Default Constructor.
	 */
	Library()
	{
	};

	/**
	 * �� ������ ���.
	 *
	 * �� ������ ����ϸ鼭 ���� ���ݵ� (intervalArray) ���� �������� �˻��Ͽ�
	 * �������� ����� �ش� �������� Ȯ�� (expand) �� �ߺ� ������ �����Ѵ�.
	 */
	void enroll(const Interval &interval)
	{
		bool intersected = false;
		for (size_t i = 0; i < intervalArray.size(); i++)
			if (intervalArray[i].intersects(interval) == true)
			{
				intervalArray[i].expand(interval);
				intersected = true;
			}
		
		if (intersected == true)
			adjust();
		else
			intervalArray.push_back(interval);
	};

	/**
	 * �������� ���νð� �� ���޽ð��� ���.
	 */
	void print()
	{
		sort(intervalArray.begin(), intervalArray.end());

		size_t stay = 0;
		size_t idle = 0;

		for (size_t i = 0; i < intervalArray.size(); i++)
		{
			stay = max(stay, intervalArray[i].stay());

			if (i >= 1 && intervalArray[i].begin > intervalArray[i - 1].end)
				idle = max(idle, intervalArray[i].begin - intervalArray[i - 1].end);
		}
		cout << stay << " " << idle << endl;
	}

private:
	/** 
	 * �������� ���ݵ��� ����.
	 *
	 * ���ݵ� (intervalArray) ���� �������� �����ϴ� �� �˻��ϰ� �����Ѵ�.
	 * �������� �����, �� ����(A)�� �� ������ ������(A+B)���� Ȯ���� ��, �ٸ� �ϳ��� ����(B)�� ����.
	 */
	void adjust()
	{
		while (true)
		{
			bool expanded = false;

			for (int i = intervalArray.size() - 1; i >= 1; i--)
				for (int j = i - 1; j >= 0; j--)
				{
					if (intervalArray[i].intersects(intervalArray[j]))
					{
						intervalArray[i].expand(intervalArray[j]);

						intervalArray.erase(intervalArray.begin() + j);
						i--;

						expanded = true;
					}
				}

			if (expanded == false)
				break;
		}
	};
};

int main()
{
	Library library;
	size_t size;

	cin >> size;
	for (size_t i = 0; i < size; i++)
	{
		size_t begin, end;
		cin >> begin >> end;

		library.enroll(Interval(begin, end));
	}

	library.print();

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}