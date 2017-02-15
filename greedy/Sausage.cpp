#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Sausage
{
private:
	int width;
	int length;

public:
	Sausage(int width, int length)
	{
		//if (length > width)
		//	swap(length, width);

		this->width = width;
		this->length = length;
	};

	auto less1(const Sausage &obj) const -> bool
	{
		return width < obj.width;
	};
	auto less2(const Sausage &obj) const -> bool
	{
		return less1(obj) || (length < obj.length);
	};

	void print() const
	{
		cout << width << " " << length << endl;
	}
};

struct compare1
{
	auto operator()(const Sausage &obj1, const Sausage &obj2) -> bool
	{
		return obj1.less1(obj2);
	};
};
struct compare2
{
	auto operator()(const Sausage &obj1, const Sausage &obj2) -> bool
	{
		return obj2.less1(obj2);
	};
};

int main()
{
	vector<Sausage> sausageArray;
	size_t size;

	cin >> size;
	for (size_t i = 0; i < size; i++)
	{
		int width, length;
		cin >> width >> length;

		sausageArray.push_back(Sausage(width, length));
	}

	sort(sausageArray.begin(), sausageArray.end(), compare1());
	sort(sausageArray.begin(), sausageArray.end(), compare2());

	vector<Sausage>::iterator it = sausageArray.begin()++;
	vector<Sausage>::iterator prevIt = sausageArray.begin();
	size_t prepareHours = 1;
	
	for (; it != sausageArray.end(); it++)
	{
		it->print();
	}

	cout << prepareHours;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}