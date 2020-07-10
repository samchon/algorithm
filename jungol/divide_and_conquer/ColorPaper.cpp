#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

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

public:
	/** 
	 * Construct from members.
	 *
	 * 입력된 가로 길이가 더 크면, 가로와 세로의 값을 바꾼다.
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
	 * 현재의 Paper가 대상 Paper보다 작은지 비교. 
	 * 가로 크기부터 비교, 가로 크기가 같을 때는 세로 크기를 비교
	 */
	auto operator<(const Paper &obj) const -> bool
	{
		if (width == obj.width)
			return height < obj.height;
		else
			return width < obj.width;
	};

	/**
	 * 현재의 Paper에 타깃 Paper를 담을(얹을) 수 있는가
	 */
	auto containable(const Paper &obj) const -> bool
	{
		return (width >= obj.width && height >= obj.height)
			|| (width >= obj.height && height >= obj.width);
	};
};

int main()
{
	vector<Paper> paperArray;
	vector<size_t> sizeArray;
	size_t size;
	
	// --------------------------------------------
	// 데이터 입력
	// --------------------------------------------
	cin >> size;
	paperArray.reserve(size);
	sizeArray.assign(size, 1);

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
	// 종이 배열을 오름차순으로 정렬
	sort(paperArray.begin(), paperArray.end());

	// 다이나믹으로 크기배열을 구성
	for (size_t i = 1; i < paperArray.size(); i++)
		for (size_t j = 0; j < i; j++)
			if (paperArray[i].containable(paperArray[j]) && sizeArray[i] < sizeArray[j] + 1)
			{
				// i번째 종이에 j번째 종이를 얹을 수 있다면,
				// j번째 종이까지 얹었던 종이 개수에 +1
				sizeArray[i] = sizeArray[j] + 1;
			}

	// 무엇이 가장 큰가
	size_t maxSize = 0;
	for (size_t i = 0; i < sizeArray.size(); i++)
		maxSize = max(maxSize, sizeArray[i]);
	
	// --------------------------------------------
	// 출력
	// --------------------------------------------
	cout << (maxSize) << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}