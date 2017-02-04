#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned long long uint64;
using namespace std;

class Histogram
	: public vector<uint64>
{
public:
	Histogram()
		: vector<uint64>()
	{
		// 7 2 1 4 5 1 3 3

		size_t size;
		cin >> size;

		this->assign(size, 0);
		for (size_t i = 0; i < size; i++)
			cin >> this->at(i);
	};

	auto area() const -> uint64
	{
		return this->area(0, this->size());
	};

private:
	auto area(size_t begin, size_t end) const -> uint64
	{
		if (begin + 1 == end)
			return this->at(begin);

		size_t mid = (begin + end) / 2;
		uint64 ret = max(this->area(begin, mid), this->area(mid, end));

		size_t lo = mid - 1;
		size_t hi = mid;
		uint64 height = min(this->at(lo), this->at(hi));

		ret = max(ret, height * 2);

		while (lo > begin || hi < end)
		{
			if (hi < end && (lo == begin || this->at(lo - 1) < this->at(hi)))
				height = min(height, min(height, this->at(hi++)));
			else if (lo > begin)
				height = min(height, this->at(--lo));

			ret = max(ret, height * (hi - lo));
		}
		return ret;
	};
};

int main()
{
	Histogram histogram;
	cout << histogram.area() << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}