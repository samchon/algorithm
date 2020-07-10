#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/**
 * 종이 클래스
 */
class Paper
{
private:
	/**
	 * 가로 길이
	 */
	int width;

	/**
	 * 세로 길이
	 */
	int height;

	// 현재 종이에 얹을 수 있는 종이들
	vector<const Paper*> putArray;

public:
	/** 
	 * Construct from members.
	 *
	 * @param width 가로 길이
	 * @param height 세로 길이
	 */
	Paper(int width, int height)
	{
		if (width > height)
			swap(width, height);

		this->width = width;
		this->height = height;
	};
	
	/**
	 * 현재 종이에 다른 종이를 얹는다.
	 */
	void put(const Paper *paper)
	{
		if (this == paper)
			return;

		if ((width >= paper->width && height >= paper->height) ||
			(width >= paper->height && height >= paper->width))
		{
			putArray.push_back(paper);
		}
	};

	/**
	 * 현재 종이에 얹을 수 있는 최대 종이 수를 구함.
	 */
	auto count() const -> size_t
	{
		return count(1, {});
	};

private:
	/**
	 * 현재 종이에 얹을 수 있는 최대 종이 수를 구함.
	 * 재귀 탐색을 수행.
	 *
	 * @param step 이미 얹혀있는 종이의 숫자
	 * @param stacked 이미 얹혀있는 종이들. 중복 방지를 위함
	 */
	auto count(size_t step, set<const Paper*> stacked) const -> size_t
	{
		stacked.insert(this);

		size_t size = step;

		for (size_t i = 0; i < putArray.size(); i++)
			if (stacked.count(putArray[i]) != 0)
				continue;
			else
				size = max(size, putArray[i]->count(step + 1, stacked));

		return size;
	};
};

int main()
{
	vector<Paper> paperArray;
	size_t size;

	// --------------------------------------------
	// 데이터 입력
	// --------------------------------------------
	cin >> size;
	paperArray.reserve(size);

	for (size_t i = 0; i < size; i++)
	{
		int width;
		int height;

		cin >> width >> height;
		paperArray.push_back(Paper(width, height));
	}

	// --------------------------------------------
	// 계산
	// --------------------------------------------
	// 종이를 얹어봄
	for (size_t i = 0; i < paperArray.size(); i++)
		for (size_t j = 0; j < paperArray.size(); j++)
			if (i == j)
				continue;
			else
				paperArray[i].put(&paperArray[j]);
	
	// 최대로 얹을 수 있는 종이 수를 계산
	size_t maxSize = 0;
	for (size_t i = 0; i < paperArray.size(); i++)
		maxSize = max(maxSize, paperArray[i].count());

	// 출력
	cout << maxSize << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}