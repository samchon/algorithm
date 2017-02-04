#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

/**
 * 하노이 타워
 * 틀린 값이 나온다
 *
 * 참고: http://stackoverflow.com/questions/12545231/tower-of-hanoi-edit-k-peg-solution
 */
class Hanoi
{
private:
	size_t disk;
	vector<stack<int>> towerStackArray;

	size_t moved;
	string message;

public:
	Hanoi(size_t disk)
	{
		this->disk = disk;
		this->moved = 0;

		towerStackArray.assign(4, stack<int>());
		for (int i = disk - 1; i >= 0; i--)
			towerStackArray[0].push(i);
		
		vector<size_t> freePegs;
		for (size_t i = 0; i < disk; i++)
			freePegs.push_back(i);

		iterate(disk, 0, 3, {0, 1, 2});
	};

private:
	void iterate(size_t disk, size_t source, size_t dest, vector<size_t> freePegs)
	{
		if (disk == 1)
		{
			moveDisk(source, dest);
			return;
		}

		size_t p = (freePegs.size() >= 2) ? disk / 2 : disk - 1;
		size_t middle = freePegs.back();

		freePegs.pop_back();
		freePegs.push_back(dest);
		iterate(p, source, middle, freePegs);

		freePegs.push_back(source);
		iterate(p, middle, dest, freePegs);

		freePegs.pop_back();
		iterate(disk - p, source, dest, freePegs);
	};

	void moveDisk(size_t from, size_t to)
	{
		int disk = towerStackArray[from].top();
		towerStackArray[from].pop();
		towerStackArray[to].push(disk);

		message += to_string(disk + 1) + " : " + char(from + 'A') + "->" + char(to + 'A') + "\n";
		moved++;
	};

public:
	void print() const
	{
		cout << moved << endl;
		cout << message << endl;
	};
};

int main()
{
	size_t disk;
	cin >> disk;

	Hanoi hanoi(disk);
	hanoi.print();

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}