#include <iostream>
#include <array>
#include <vector>
#include <utility>

using namespace std;

class StickerMatrix;
class Sticker;

class StickerMatrix
	: public array<vector<Sticker*>, 2>
{
private:
	typedef public array<vector<Sticker*>, 2> super;

public:
	StickerMatrix(size_t width);

	auto valueAt(size_t x, size_t y) const -> int;
	void pop(size_t x, size_t y);

	auto width() const -> size_t;
	auto height() const -> size_t;

	void estimate();

private:
	void determine(Sticker*);
};

class Sticker
{
public:
	StickerMatrix *matrix;
	size_t x;
	size_t y;
	int value;

public:
	Sticker(StickerMatrix *matrix, size_t x, size_t y, int value);

	auto estimateValue() const -> int;
};

struct COMPARE_STICKER
{
	auto operator()(Sticker *prev, Sticker *next) const -> bool
	{
		return prev->estimateValue() > next->estimateValue();
	}
};

int main()
{
	size_t caseSize;
	cin >> caseSize;

	for (size_t i = 0; i < caseSize; i++)
	{
		size_t width;
		cin >> width;

		StickerMatrix matrix(width);

		for (size_t y = 0; y < 2; y++)
			for (size_t x = 0; x < width; x++)
			{
				int value;
				cin >> value;

				matrix[y][x] = new Sticker(&matrix, x, y, value);
			}

		matrix.estimate();
	}
	system("pause");
}

StickerMatrix::StickerMatrix(size_t width)
	: super()
{
	at(0) = vector<Sticker*>(width);
	at(1) = vector<Sticker*>(width);
};

auto StickerMatrix::valueAt(size_t x, size_t y) const -> int
{
	if (x < 0 || x >= width())
		return 0;
	if (y < 0 || y >= height())
		return 0;

	return at(y).at(x)->value;
};
void StickerMatrix::pop(size_t x, size_t y)
{
	if (x < 0 || x >= width())
		return;
	if (y < 0 || y >= height())
		return;

	at(y).at(x) = nullptr;
}

auto StickerMatrix::width() const -> size_t
{
	return at(0).size();
};
auto StickerMatrix::height() const -> size_t
{
	return size();
};

void StickerMatrix::estimate()
{
	vector<Sticker*> stickerArray;

	for (size_t y = 0; y < height(); y++)
		for (size_t x = 0; x < width(); x++)
			stickerArray.push_back(at(y).at(x));

	sort(stickerArray.begin(), stickerArray.end(), COMPARE_STICKER());

	int value = 0;
	for (size_t i = 0; i < stickerArray.size(); i++)
	{
		Sticker *sticker = stickerArray[i];
		if (at(sticker->y).at(sticker->x) == nullptr)
			continue;

		cout << "\t" << sticker->x << ", " << sticker->y << ": $" << sticker->value << endl;

		determine(sticker);
		value += sticker->value;
	}

	cout << "$" << value << endl;
}
void StickerMatrix::determine(Sticker *sticker)
{
	size_t x = sticker->x, y = sticker->y;

	pop(x + 1, y);
	pop(x - 1, y);
	pop(x, y - 1);
	pop(x, y + 1);
}

Sticker::Sticker(StickerMatrix *matrix, size_t x, size_t y, int value)
{
	this->matrix = matrix;
	this->x = x;
	this->y = y;
	this->value = value;
}
auto Sticker::estimateValue() const -> int
{
	int value = this->value;
	value -= matrix->valueAt(x - 1, y);
	value -= matrix->valueAt(x + 1, y);
	value -= matrix->valueAt(x, y - 1);
	value -= matrix->valueAt(x, y + 1);

	return value;
}