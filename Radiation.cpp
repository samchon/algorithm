#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

class ZerglingMatrix
	: public vector<vector<int>>
{
private:
	typedef vector<vector<int>> super;

	static const int VITAL = 3;
	int clearedSeconds;

public:
	ZerglingMatrix(size_t width, size_t height)
		: super(height, vector<int>(width))
	{
	};

	using super::at;
	auto at(size_t x, size_t y) -> int&
	{
		return at(y).at(x);
	};

	auto width() const -> size_t
	{
		return at(0).size();
	};
	auto height() const -> size_t
	{
		return size();
	};

	void radiate(size_t x, size_t y)
	{
		radiate(x, y, 0);

		int elapsed = 0;
		size_t alived = 0;
		
		for (size_t x = 0; x < width(); x++)
			for (size_t y = 0; y < height(); y++)
			{
				int val = at(x, y);

				if (val == NULL)
					continue;
				else if (val == INT_MAX)
					alived++;
				else
					elapsed = max(elapsed, val);
			}

		cout << elapsed << endl;
		cout << alived << endl;
	};

private:
	void radiate(size_t x, size_t y, int elapsed)
	{
		if (x < 0 || x >= width() || y < 0 || y >= height())
		{
			// 좌표를 벗어난 지점인가?
			return;
		}
		else if (this->at(x, y) == NULL)
		{
			// 빈 공간인가?
			return;
		}
		else if ((VITAL + elapsed) >= this->at(x, y))
		{
			// 저글링이 더 빨리 죽었을 수 있는가?
			// 즉, 이미 감염된 대상인가?
			return;
		}

		// 현 저글링이 죽은 시간: 현재 시간 + 3초
		this->at(x, y) = VITAL + elapsed;
		
		// 상하좌우 모두 감염을 시킨다
		radiate(x - 1, y, elapsed + 1); // 좌
		radiate(x + 1, y, elapsed + 1); // 우
		radiate(x, y - 1, elapsed + 1); // 상
		radiate(x, y + 1, elapsed + 1); // 하
	};
};

int main()
{
	size_t width, height;
	cin >> width >> height;

	ZerglingMatrix matrix(width, height);

	for (size_t y = 0; y < height; y++)
	{
		string line;
		cin >> line;

		for (size_t x = 0; x < width; x++)
			if (line[x] == '1')
				matrix.at(x, y) = INT_MAX;
			else
				matrix.at(x, y) = NULL;
	}

	size_t x, y;
	cin >> x >> y;

	matrix.radiate(x - 1, y - 1);

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}