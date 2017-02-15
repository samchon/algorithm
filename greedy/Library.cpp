#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 간격 클래스.
 */
class Interval
{
public:
	/**
	 * 시작 시간.
	 */
	size_t begin;

	/**
	 * 종료 시간.
	 */
	size_t end;

	/**
	 * Construct from members.
	 *
	 * @param begin 시작 시간
	 * @param end 종료 시간
	 */
	Interval(size_t begin, size_t end)
	{
		this->begin = begin;
		this->end = end;
	};

	/**
	 * 현재의 간격과 타깃 간격에 교집합이 있는 지 검사.
	 *
	 * @param interval 타깃 간격
	 * @return 교집합이 있는 지 여부
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
	 * 대소 비교 함수.
	 * 
	 * 공부 시간이 더 작은 지 검사한다.
	 */
	auto operator<(const Interval &interval) const -> bool
	{
		if (begin == interval.begin)
			return end < interval.end;
		else
			return begin < interval.begin;
	};

	/**
	 * Get 도서관에 머무른 시간.
	 */
	auto stay() -> size_t
	{
		return end - begin;
	};

	/** 
	 * 현재의 간격을 타깃 간격과의 합집합으로 확대.
	 *
	 * @param interval 타깃 간격
	 */
	void expand(const Interval &interval)
	{
		begin = min(begin, interval.begin);
		end = max(end, interval.end);
	};
};

/** 
 * 도서관 클래스.
 */
class Library
{
private:
	/**
	 * 간격 배열.
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
	 * 새 간격을 등록.
	 *
	 * 새 간격을 등록하면서 기존 간격들 (intervalArray) 와의 교집합을 검사하여
	 * 교집합이 존재시 해당 교집합을 확대 (expand) 및 중복 구간을 삭제한다.
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
	 * 도서관의 공부시간 및 유휴시간을 출력.
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
	 * 도서관의 간격들을 조정.
	 *
	 * 간격들 (intervalArray) 간에 교집합이 존재하는 지 검사하고 조정한다.
	 * 교집합이 존재시, 한 간격(A)을 두 간격을 합집합(A+B)까지 확대한 후, 다른 하나의 구간(B)을 삭제.
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