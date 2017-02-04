#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Point
{
public:
	double x;
	double y;

public:
	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	};
};

class Shape
	: public vector<Point>
{
private:
	typedef vector<Point> super;

public:
	using super::super;

	/**
	 * 다각형 (polygon) 의 넓이를 구하는 함수.
	 *
	 * http://www.mathopenref.com/coordpolygonarea2.html
	 */
	virtual auto calcArea() const -> double
	{
		double area = 0.0;
		size_t j = this->size() - 1;

		for (size_t i = 0; i < this->size(); i++)
		{
			// area += (x1 + x2) * (y1 - y2)
			area += (this->at(j).x + this->at(i).x) * (this->at(j).y - this->at(i).y);
			j = i;
		}

		// 리턴값에 절대값만 붙여주면 됨
		return abs(area / 2.0);
	};
};

int main()
{
	Shape shape;
	size_t side;

	cin >> side;
	shape.reserve(side);
	
	for (size_t i = 0; i < side; i++)
	{
		double x, y;
		cin >> x >> y;

		shape.emplace_back(x, y);
	}

	printf("%.1lf", shape.calcArea());

#ifdef _WIN32
	system("pause");
#endif
}