#include <iostream>
#include <vector>

using namespace std;

class ColoredPaper
{
private:
	vector<vector<int>> matrix;

	static const int WHITE = 0;
	static const int BLUE = 1;

public:
	ColoredPaper()
	{
		size_t size;
		cin >> size;

		matrix.assign(size, vector<int>(size, 0));

		for (size_t r = 0; r < size; r++)
			for (size_t c = 0; c < size; c++)
				cin >> matrix[r][c];
	};

	void calcSize()
	{
		const pair<int, int> &sizePair = calcSize(0, 0, matrix.size());

		cout << sizePair.first << endl;
		cout << sizePair.second;
	};

private:
	pair<int, int> calcSize(int row, int col, int size)
	{
		pair<int, int> sizePair(0, 0);
		if (size == 0)
			return sizePair;

		int color = matrix[row][col];

		bool equals = true;

		for (int r = row; r < row + size; r++)
			for (int c = col; c < col + size; c++)
				if (matrix[r][c] != color)
				{
					equals = false;
					break;
				}

		if (equals == true)
			if (color == WHITE)
				sizePair.first++;
			else
				sizePair.second++;
		else
		{
			for (int r = row; r < (row + size); r += size / 2)
				for (int c = col; c < (col + size); c += size / 2)
				{
					const pair<int, int> &mySizePair = calcSize(r, c, size/2);

					sizePair.first += mySizePair.first;
					sizePair.second += mySizePair.second;
				}
		}
		return sizePair;
	};
};

int main()
{
	ColoredPaper colorPaper;
	colorPaper.calcSize();

	return 0;
}